#include "speckle.h"
#include "DaqThread.h"

extern SpeckleClass *speckle;


DaqThread::DaqThread(QObject *parent)
: QThread(parent)
{
	int junk=0;
}

/*****************************************************************/
void DaqThread::run()
{

	QTime DOtimer;
	int t_now;
	//QThread::exec();

	//TestTask();
	//return;

	speckle->daq_status=ACQUIRING;
	if(speckle->pulse_gen.enableDO)
	{
		if(CreateDOTask()>0)
		{
			StartDOTask();	
			if(speckle->pulse_gen.stop_condition==DO_STOP_WITH_TIME)
				DOtimer.start();
		}
		else
			speckle->pulse_gen.enableDO=false;
	}

	if(speckle->daq_mode==BASIC_DAQ)
		AcquireBasicDAQ();
	else if(speckle->daq_mode==TRIGGERED_DAQ)
		AcquireTriggeredDAQ();
    else if(speckle->daq_mode==TASK_DAQ)
        TestTask();
    else if (speckle->daq_mode==BASIC_DAQ_TDMS)
        AcquireBasicDAQ_tdmsLogging();

	if(speckle->pulse_gen.enableDO && speckle->pulse_gen.stop_condition==DO_STOP_WITH_DAQ)
		StopDOTask();
	else
	{
		// wait for DO to finish
		bool keep_going=false;
		if(speckle->pulse_gen.enableDO)
			keep_going=true;
		while(keep_going)
		{
			if(speckle->pulse_gen.status == DO_IDLE) // stop button was pressed
				keep_going=false;
			if(speckle->pulse_gen.stop_condition==DO_STOP_WITH_CAMERA && (speckle->acquire_flag!=ACQUISITION_MODE))
				keep_going=false;
			else if(speckle->pulse_gen.stop_condition==DO_STOP_WITH_TIME)
			{
				t_now=DOtimer.elapsed(); 
				if( ((float)(t_now)/1.0e3) >= speckle->pulse_gen.DO_total_duration)
					keep_going=false;
			}
			Sleep(50);
		}
		StopDOTask();
	}
	speckle->daq_status=IDLE;
}
/*********************************************************************/
void DaqThread::AcquireBasicDAQ(void)
{
	int keep_going=1;
	TaskHandle  taskHandle=0;
	uInt32 samp_in_one_sec;
	int32 tot_samples_read, samples_read;
	double *p;

	if(DAQmxCreateTask("",&taskHandle)<0)
	{
		keep_going=0;
		emit postSpeckleMessage(QString("Error in DAQmxCreateTask(). Aborting daq."));
	}

	if(DAQmxCreateAIVoltageChan(taskHandle, speckle->daq_use_ai_chan_list.toUtf8(),
		"", speckle->ai_input_config, -10.0, 10.0, DAQmx_Val_Volts, NULL)<0)
	{
		keep_going=0;
		emit postSpeckleMessage(QString("Error in DAQmxCreateAIVoltageChan(). Aborting daq."));
	}

	if(DAQmxCfgSampClkTiming(taskHandle, NULL, speckle->daq_samp_rate, DAQmx_Val_Rising,
		DAQmx_Val_FiniteSamps, speckle->samples_per_channel)<0)
	{
		keep_going=0;
		emit postSpeckleMessage(QString("Error in DAQmxCfgSampClkTiming(). Aborting daq."));
	}

	samp_in_one_sec=(uInt32)(speckle->daq_samp_rate);
	tot_samples_read=0;

	if(speckle->daq_write_continuously)
	{
		speckle->daq_data.resize(2*samp_in_one_sec*speckle->num_daq_chan_in_use);
		initialize_daq_output_file();
	}
	else
		speckle->daq_data.resize(speckle->samples_per_channel*speckle->num_daq_chan_in_use);
	speckle->daq_data.fill(0.0); // zero out the array

	if(DAQmxStartTask(taskHandle)<0)
	{
		keep_going=0;
		emit postSpeckleMessage(QString("Error in DAQmxStartTask(). Aborting daq."));
	}

	p=&(speckle->daq_data[0]);
	while(keep_going)
	{
		DAQmxReadAnalogF64(taskHandle, samp_in_one_sec, 2.0, DAQmx_Val_GroupByScanNumber,
			p, samp_in_one_sec*speckle->num_daq_chan_in_use, &samples_read, NULL);
		tot_samples_read += samples_read;
		if(tot_samples_read == speckle->samples_per_channel)
			keep_going=0;
		
		if(speckle->daq_write_continuously)
			// save current samples read to file
			daq_stream.writeRawData((const char *)(p), samp_in_one_sec*speckle->num_daq_chan_in_use*sizeof(double));			
		else
			p += samples_read*speckle->num_daq_chan_in_use;
		emit postSpeckleMessage(QString("daq acquired %1 samples").arg(tot_samples_read));

		if(speckle->daq_status==IDLE)
			keep_going=0;
		if(speckle->stop_daq_with_camera && (speckle->acquire_flag!=ACQUISITION_MODE))
			keep_going=0;
	}
	speckle->daq_samples_read=tot_samples_read;
	emit postSpeckleMessage(QString("daq complete"));
	DAQmxStopTask(taskHandle);
	DAQmxClearTask(taskHandle);

	if(speckle->daq_status != IDLE)
	{
		// save data
		if(speckle->daq_write_continuously)
			daq_file.close();
		else
		{
                if(speckle->daq_output_file_format==MATLAB_OUTPUT && (speckle->save_raw || speckle->save_SC))
                    write_daq_to_mat_file();
                else if(speckle->daq_output_file_format==RAW_BINARY_OUTPUT)
                    write_daq_to_raw_file((void *)&(speckle->daq_data[0]), sizeof(double));
            }
	}
}
/*********************************************************************/
void DaqThread::AcquireTriggeredDAQ(void)
{
	int keep_going=1;
	TaskHandle  counterTask=0;
	TaskHandle  aiTask=0;
	TaskHandle  aoTask=0;
	int32 tot_samples_read, samples_read;
	short *p;
	//double *p;
	int err_code;
	char err_str[512];
	int t_now;
	QString dev_name=speckle->daq_dev_list[speckle->curr_daq_dev_index];

	if(DAQmxCreateTask("",&counterTask)<0)
	{
		keep_going=0;
		emit postSpeckleMessage(QString("Error in DAQmxCreateTask(). Aborting daq."));
	}
	// second arg should be "Dev1/Ctr0"
	if(DAQmxCreateCOPulseChanFreq(counterTask, QString(dev_name+"/Ctr0").toUtf8(),
		"", DAQmx_Val_Hz, DAQmx_Val_Low, 0.0, speckle->daq_samp_rate, 0.5)<0)
	{
		keep_going=0;
		emit postSpeckleMessage(QString("Error in DAQmxCreateCOPulseChanFreq(). Aborting daq."));
	}
	// second arg should be "/Dev1/PFI0"
	if(DAQmxCfgDigEdgeStartTrig(counterTask, QString("/"+dev_name+"/PFI0").toUtf8(),
		DAQmx_Val_Rising)<0)
	{
		keep_going=0;
		emit postSpeckleMessage(QString("Error in DAQmxCfgDigEdgeStartTrig(). Aborting daq."));
	}
	if(DAQmxCfgImplicitTiming(counterTask, DAQmx_Val_FiniteSamps, speckle->daq_samples_per_illum_region)<0)
	{
		keep_going=0;
		emit postSpeckleMessage(QString("Error in AQmxCfgImplicitTiming(). Aborting daq."));
	}
	if(DAQmxSetStartTrigRetriggerable(counterTask, 1)<0)
	{
		keep_going=0;
		emit postSpeckleMessage(QString("Error in DAQmxSetStartTrigRetriggerable(). Aborting daq."));
	}

	if(DAQmxCreateTask("",&aiTask)<0)
	{
		keep_going=0;
		emit postSpeckleMessage(QString("Error in DAQmxCreateTask(). Aborting daq."));
	}
	if(DAQmxCreateAIVoltageChan(aiTask, speckle->daq_use_ai_chan_list.toUtf8(),
		"", speckle->ai_input_config, -10.0, 10.0, DAQmx_Val_Volts, NULL)<0)
	{
		keep_going=0;
		emit postSpeckleMessage(QString("Error in DAQmxCreateAIVoltageChan(). Aborting daq."));
	}
	// second argument should create "/Dev1/Ctr0InternalOutput"
	if(DAQmxCfgSampClkTiming(aiTask, QString("/"+dev_name+"/Ctr0InternalOutput").toUtf8(),
		speckle->daq_samp_rate, DAQmx_Val_Rising,
		DAQmx_Val_ContSamps, speckle->daq_samples_per_illum_region)<0)
	{
		keep_going=0;
		emit postSpeckleMessage(QString("Error in DAQmxCfgSampClkTiming(). Aborting daq."));
	}	

	// estimate the total number of samples that will be acquired
    float t=speckle->daq_duration;
	uInt64 approx_tot_samples_to_collect = (uInt64)(t*speckle->daq_samp_rate*((float)(speckle->num_daq_chan_in_use)));

	if(speckle->daq_write_continuously)
	{
		speckle->daq_data16.resize(2*speckle->daq_samples_per_illum_region*speckle->num_daq_chan_in_use);
		initialize_daq_output_file();
	}
	else
		speckle->daq_data16.resize(approx_tot_samples_to_collect); // hold everything in memory and write at end
	speckle->daq_data16.fill(0);	
	//speckle->daq_data.resize(approx_tot_samples_to_collect);
	//speckle->daq_data.fill(0);	

	// set up analog output
	generate_AOM_voltages();

		// analog output task
	if(DAQmxCreateTask("",&aoTask)<0)
	{
		keep_going=0;
		emit postSpeckleMessage(QString("Error in DAQmxCreateTask() for ao. Aborting daq."));
	}
	if(DAQmxCreateAOVoltageChan(aoTask,QString(dev_name+"/ao0").toUtf8(),"",
		-10.0,10.0,DAQmx_Val_Volts,NULL)<0)
	{
		keep_going=0;
		emit postSpeckleMessage(QString("Error in DAQmxCreateAOVoltageChan(). Aborting daq."));
	}
	if(DAQmxCfgSampClkTiming(aoTask, QString("/"+dev_name+"/Ctr0InternalOutput").toUtf8(),
		speckle->daq_samp_rate, DAQmx_Val_Rising,
		DAQmx_Val_ContSamps, speckle->daq_samples_per_illum_region)<0)
	{
		keep_going=0;
		emit postSpeckleMessage(QString("Error in DAQmxCfgSampClkTiming() in analog output. Aborting daq."));
	}
	int32 samps_written;
	if(DAQmxWriteAnalogF64(aoTask, speckle->daq_samples_per_illum_region, false, -1, 
		DAQmx_Val_GroupByChannel, &(speckle->ao_vec[0]), &samps_written, NULL)<0)
	{
		keep_going=0;
		emit postSpeckleMessage(QString("Error in DAQmxWriteAnalogF64(). %1 samples written. Aborting daq.").arg(samps_written));
	}
	
	if((err_code=DAQmxStartTask(aiTask))<0)
	{
		keep_going=0;
		emit postSpeckleMessage(QString("Error in DAQmxStartTask() for analog input (error code %1). Aborting daq.").arg(err_code));
		DAQmxGetErrorString(err_code, err_str, 512);
		emit postSpeckleMessage(QString(err_str));
	}
	if((err_code=DAQmxStartTask(aoTask))<0)
	{
		keep_going=0;
		emit postSpeckleMessage(QString("Error in DAQmxStartTask() for analog output (error code %1). Aborting daq.").arg(err_code));
		DAQmxGetErrorString(err_code, err_str, 512);
		emit postSpeckleMessage(QString(err_str));
	}
	if((err_code=DAQmxStartTask(counterTask))<0)
	{
		keep_going=0;
		emit postSpeckleMessage(QString("Error in DAQmxStartTask() for counter (error code %1). Aborting daq.").arg(err_code));
		DAQmxGetErrorString(err_code, err_str, 512);
		emit postSpeckleMessage(QString(err_str));
	}

	p=&(speckle->daq_data16[0]);
	//p=&(speckle->daq_data[0]);

	// start a timer to keep track of elapsed time	
	QTime timer;
	timer.start();

	tot_samples_read=0;
	int t_update=0;
	while(keep_going)
	{
        DAQmxReadBinaryI16(aiTask, speckle->daq_samples_per_illum_region, 100.0, DAQmx_Val_GroupByScanNumber,
			p, speckle->daq_samples_per_illum_region*speckle->num_daq_chan_in_use, &samples_read,  NULL);
		//DAQmxReadAnalogF64(aiTask, speckle->daq_samples_per_illum_region, 10.0, DAQmx_Val_GroupByScanNumber,
		//	p, speckle->daq_samples_per_illum_region*speckle->num_daq_chan_in_use, &samples_read, NULL);
		tot_samples_read += samples_read;

		t_now=timer.elapsed(); // avoids calling elapsed() multiple times
		if(t_now-t_update > 1000) // update display approx every 1 sec
		{
			emit postSpeckleMessage(QString("daq acquired %1 of %2 samples, elapsed time=%3").arg(tot_samples_read).
				arg(approx_tot_samples_to_collect).arg((float)(t_now)/1e3));
			t_update=t_now;
		}

		if((float)(t_now)/1e3 >= speckle->daq_duration)
			keep_going=0;
		
		if(speckle->daq_write_continuously)
		{
			// save current samples read to file
			daq_stream.writeRawData((const char *)(p), speckle->daq_samples_per_illum_region*speckle->num_daq_chan_in_use*sizeof(short));			
		}
		else
			p += samples_read*speckle->num_daq_chan_in_use;
		
		if(speckle->daq_status==IDLE) // stop button was pressed
			keep_going=0;		
	}
	speckle->daq_samples_read=tot_samples_read;
	emit postSpeckleMessage(QString("daq complete"));

	DAQmxStopTask(counterTask);
	DAQmxStopTask(aiTask);
	DAQmxStopTask(aoTask);
	DAQmxClearTask(counterTask);
	DAQmxClearTask(aiTask);
	DAQmxClearTask(aoTask);

	// reset analog output line to 0
	float64     data[1] = {0.0};
	DAQmxCreateTask("",&aoTask);
	DAQmxCreateAOVoltageChan(aoTask,QString(dev_name+"/ao0").toUtf8(),"",
		-10.0,10.0,DAQmx_Val_Volts,NULL);
	DAQmxStartTask(aoTask);
	DAQmxWriteAnalogF64(aoTask,1,1,10.0,DAQmx_Val_GroupByChannel,data,NULL,NULL);
	DAQmxStopTask(aoTask);
	DAQmxClearTask(aoTask);


	if(speckle->daq_write_continuously)
	{							
		daq_file.close();
	}
	else
		write_daq_to_raw_file((void *)&(speckle->daq_data16[0]), sizeof(short));
	//write_daq_to_raw_file((void *)&(speckle->daq_data[0]), sizeof(double));

	speckle->ao_vec.clear();
	speckle->daq_data16.clear();
	speckle->daq_status=IDLE;
}
/*********************************************************************/
void DaqThread::write_daq_to_raw_file(void *p, int bytes_per_sample)
{
	QFile file(speckle->filename+".daq");
	file.open(QIODevice::WriteOnly);
	QDataStream out(&file);
	out.writeRawData((const char *)(&(speckle->daq_samp_rate)), sizeof(double));
	out.writeRawData((const char *)(&(speckle->num_daq_chan_in_use)), sizeof(int));
	long lfoo=(long)(speckle->daq_samples_read);
	out.writeRawData((const char *)(&(lfoo)), sizeof(long));
	out.writeRawData((const char *)(p), speckle->daq_samples_read*speckle->num_daq_chan_in_use*bytes_per_sample);
	file.close();

    // another test
}
/*********************************************************************/
void DaqThread::initialize_daq_output_file(void)
{
	daq_file.setFileName(speckle->filename+".daq");
	daq_file.open(QIODevice::WriteOnly);
	//QDataStream daq_stream(&file);
	daq_stream.setDevice(&daq_file);
	daq_stream.writeRawData((const char *)(&(speckle->daq_samp_rate)), sizeof(double));
	daq_stream.writeRawData((const char *)(&(speckle->num_daq_chan_in_use)), sizeof(int));
    long lfoo=speckle->daq_samples_per_illum_region; //-1;
	daq_stream.writeRawData((const char *)(&(lfoo)), sizeof(long));
}
/*********************************************************************/
void DaqThread::write_daq_to_mat_file(void)
{
    qDebug() << ".mat output no longer supported since x64 transition";
}
/*********************************************************************/
void DaqThread::generate_AOM_voltages(void)
{
	long i, j;
	int n;
	double t, dt, T_aom;
	double a, b, N, val;	

	speckle->ao_vec.resize(speckle->daq_samples_per_illum_region);
	speckle->ao_vec.fill(0.0);

	dt=1.0/speckle->daq_samp_rate;
	T_aom=1.0/speckle->daq_AOM_pulse_rate; // time between AOM pulses

	//emit postSpeckleMessage(QString("dt= %1, T_aom=%2").arg(dt).arg(T_aom));

	for(i=0;i<speckle->daq_samples_per_illum_region;i++)
	{
		t=(double)(i)*dt;
		if(speckle->daq_AOM_mode==TIME_DOMAIN)
		{
			n=(int)(t/T_aom);
			if((t-(float)(n)*T_aom) <= speckle->daq_AOM_pulse_width)					
				speckle->ao_vec[i]=speckle->daq_AOM_voltage;		
		}
		else if(speckle->daq_AOM_mode==FREQ_DOMAIN)
		{
			a=0.5;
			b=0.5;
			N=(double)(speckle->ao_freq_list.size());
			val=0.0;
			for(j=0;j<speckle->ao_freq_list.size();j++)
				val += cos(2*PI*speckle->ao_freq_list[j]*t);
			speckle->ao_vec[i] = speckle->daq_AOM_voltage*(a+b/N*val)+speckle->daq_AOM_offset;
		}
	}


	//// temporarily write to file to check waveform
	//QFile file("waveform.dat");
	//file.open(QIODevice::WriteOnly);
	//QDataStream out(&file);
	//out.writeRawData((const char *)(&(speckle->daq_samples_per_illum_region)), sizeof(uInt64));
	//out.writeRawData((const char *)(&(speckle->ao_vec[0])), speckle->daq_samples_per_illum_region*sizeof(double));
	//file.close();

}
/*********************************************************************/
int DaqThread::CreateDOTask(void)
{
	int32 samps_written;
	int err_code;
	char err_str[512];
	int ret=1;

	if(DAQmxCreateTask("",&FreqOutTask)<0)
	{
		emit postSpeckleMessage(QString("Error in DAQmxCreateTask() for DO. Aborting daq."));
		ret=0;
	}
	if(DAQmxCreateCOPulseChanFreq(FreqOutTask, QString(speckle->pulse_gen.DOdev_name+"/freqout").toUtf8(), "", DAQmx_Val_Hz, DAQmx_Val_Low,
		0.0, speckle->pulse_gen.DOSampFreq, 0.5)<0)
	{
		emit postSpeckleMessage(QString("Error in DAQmxCreateCOPulseChanFreq() for DO. Aborting daq."));
		ret=0;
	}
	if(DAQmxCreateTask("",&DOTask)<0)
	{
		emit postSpeckleMessage(QString("Error in DAQmxCreateTask() for DO. Aborting daq."));
		ret=0;
	}
	if(DAQmxCreateDOChan(DOTask,QString(speckle->pulse_gen.DOdev_name+"/port0/line0:7").toUtf8(),"",DAQmx_Val_ChanForAllLines)<0)
	{
		emit postSpeckleMessage(QString("Error in DAQmxCreateDOChan() for DO. Aborting daq."));
		ret=0;
	}
	if(DAQmxCfgSampClkTiming(DOTask, QString("/"+speckle->pulse_gen.DOdev_name+"/FrequencyOutput").toUtf8(),
		speckle->pulse_gen.DOSampFreq, DAQmx_Val_Rising, DAQmx_Val_ContSamps, 
		speckle->pulse_gen.num_samples)<0)
	{
		emit postSpeckleMessage(QString("Error in DAQmxCfgSampClkTiming() for DO. Aborting daq."));
		ret=0;
	}
	if((err_code=DAQmxWriteDigitalU32(DOTask, speckle->pulse_gen.num_samples, false, -1, DAQmx_Val_GroupByScanNumber,
		speckle->pulse_gen.DOdata.data(), &samps_written, NULL))<0)
	{
		emit postSpeckleMessage(QString("Error in DAQmxWriteDigitalU32() for DO. Aborting daq."));
		DAQmxGetErrorString(err_code, err_str, 512);
		emit postSpeckleMessage(QString(err_str));
		ret=0;
	}
	return(ret);

}
/*********************************************************************/
void DaqThread::StartDOTask(void)
{
	int err_code;
	char err_str[512];

	if((err_code=DAQmxStartTask(FreqOutTask))<0)
	{
		emit postSpeckleMessage(QString("Error in DAQmxStartTask() for DO freqout (error code %1). Aborting daq.").arg(err_code));
		DAQmxGetErrorString(err_code, err_str, 512);
		emit postSpeckleMessage(QString(err_str));
	}
	if((err_code=DAQmxStartTask(DOTask))<0)
	{
		emit postSpeckleMessage(QString("Error in DAQmxStartTask() for DO (error code %1). Aborting daq.").arg(err_code));
		DAQmxGetErrorString(err_code, err_str, 512);
		emit postSpeckleMessage(QString(err_str));
	}
}
/*********************************************************************/
void DaqThread::StopDOTask(void)
{
	DAQmxStopTask(DOTask);
	DAQmxClearTask(DOTask);
	DAQmxStopTask(FreqOutTask);
	DAQmxClearTask(FreqOutTask);
	speckle->pulse_gen.status = DO_IDLE;
}
/*********************************************************************/
void DaqThread::TestTask(void)
{
    int keep_going=1;
    TaskHandle  taskHandle_acq;
    TaskHandle	taskHandle1;
    TaskHandle	taskHandle2;
    int32 Wait_Time = -1;
    char errBuff[2048]={'\0'};

    // DAQmx Configure Code - Acquisition
    if(DAQmxCreateTask("",&taskHandle_acq)<0)
    {
        keep_going=0;
        DAQmxGetExtendedErrorInfo(errBuff, 2048);
        emit postSpeckleMessage(QString("Error in DAQmxCreateTask(): %1. Aborting daq.").arg(errBuff));
    }

    if(DAQmxCreateAIVoltageChan(taskHandle_acq, speckle->daq_use_ai_chan_list.toUtf8(),
        "", speckle->ai_input_config, -10.0, 10.0, DAQmx_Val_Volts, NULL)<0)
    {
        keep_going=0;
        DAQmxGetExtendedErrorInfo(errBuff, 2048);
        emit postSpeckleMessage(QString("Error in DAQmxCreateAIVoltageChan(): %1. Aborting daq.").arg(errBuff));
    }

    if(DAQmxCfgSampClkTiming(taskHandle_acq, NULL, speckle->daq_samp_rate, DAQmx_Val_Rising,
        DAQmx_Val_FiniteSamps, speckle->samples_per_channel)<0)
    {
        keep_going=0;
        DAQmxGetExtendedErrorInfo(errBuff, 2048);
        emit postSpeckleMessage(QString("Error in DAQmxCfgSampClkTiming(): %1. Aborting daq.").arg(errBuff));
    }

    // TDMS Configure Logging
    QString fname_tdms;
    fname_tdms=QString(speckle->filename+".tdms");

    //if(DAQmxConfigureLogging(taskHandle_acq,"example.tdms",DAQmx_Val_Log,"Voltage(s)",DAQmx_Val_CreateOrReplace)<0)
    if(DAQmxConfigureLogging(taskHandle_acq,fname_tdms.toUtf8(),DAQmx_Val_Log,"Voltage(s)",DAQmx_Val_CreateOrReplace)<0)
    {
        keep_going=0;
        DAQmxGetExtendedErrorInfo(errBuff, 2048);
        emit postSpeckleMessage(QString("Error in DAQmxConfigureLogging(): %1. Aborting daq.").arg(errBuff));
    }

    // DAQmx Start Code - Acquisition
    if(DAQmxStartTask(taskHandle_acq)<0)
    {
        keep_going=0;
        DAQmxGetExtendedErrorInfo(errBuff, 2048);
        emit postSpeckleMessage(QString("Error in DAQmxStartTask(): %1. Aborting daq.").arg(errBuff));
    }

    // DAQmx Configure Code - Generation
    if(DAQmxLoadTask(speckle->daq_task_name1.toUtf8(), &taskHandle1)<0)
    {
        keep_going=0;
        DAQmxGetExtendedErrorInfo(errBuff, 2048);
        emit postSpeckleMessage(QString("Error in DAQmxLoadTask() Generation 1: %1. Aborting daq.").arg(errBuff));
    }
    if(DAQmxLoadTask(speckle->daq_task_name2.toUtf8(), &taskHandle2)<0)
    {
        keep_going=0;
        DAQmxGetExtendedErrorInfo(errBuff, 2048);
        emit postSpeckleMessage(QString("Error in DAQmxLoadTask() Generation 2: %1. Aborting daq.").arg(errBuff));
    }

    // DAQmx Start Code - Generation
    if(DAQmxStartTask(taskHandle1)<0)
    {
        keep_going=0;
        DAQmxGetExtendedErrorInfo(errBuff, 2048);
        emit postSpeckleMessage(QString("Error in DAQmxStartTask() Generation 1: %1. Aborting daq.").arg(errBuff));
    }
    if(DAQmxStartTask(taskHandle2)<0)
    {
        keep_going=0;
        DAQmxGetExtendedErrorInfo(errBuff, 2048);
        emit postSpeckleMessage(QString("Error in DAQmxStartTask() Generation 2: %1. Aborting daq.").arg(errBuff));
    }

    // DAQmx Wait Code
    // A value of -1 (DAQmx_Val_WaitInfinitely) means to wait indefinitely.
    if(DAQmxWaitUntilTaskDone(taskHandle2, Wait_Time)<0)
    {
        keep_going=0;
        DAQmxGetExtendedErrorInfo(errBuff, 2048);
        emit postSpeckleMessage(QString("Error in DAQmxWaitUntilTaskDone() Generation 2: %1. Aborting daq.").arg(errBuff));
    }
    else
        emit postSpeckleMessage(QString("Generation 2 task complete."));

    if(DAQmxWaitUntilTaskDone(taskHandle_acq,Wait_Time)<0)
    {
        keep_going=0;
        DAQmxGetExtendedErrorInfo(errBuff, 2048);
        emit postSpeckleMessage(QString("Error in DAQmxWaitUntilTaskDone() Acquisition: %1. Aborting daq.").arg(errBuff));
    }
    else
        emit postSpeckleMessage(QString("Acquisition task complete."));

    //DAQmx Stop Code
    if(DAQmxStopTask(taskHandle1)<0)
    {
        keep_going=0;
        DAQmxGetExtendedErrorInfo(errBuff, 2048);
        emit postSpeckleMessage(QString("Error in DAQmxStopTask() Generation 1: %1. Aborting daq.").arg(errBuff));
    }
    if(DAQmxClearTask(taskHandle1)<0)
    {
        keep_going=0;
        DAQmxGetExtendedErrorInfo(errBuff, 2048);
        emit postSpeckleMessage(QString("Error in DAQmxClearTask() Generation 1: %1. Aborting daq.").arg(errBuff));
    }
    if(DAQmxStopTask(taskHandle2)<0)
    {
        keep_going=0;
        DAQmxGetExtendedErrorInfo(errBuff, 2048);
        emit postSpeckleMessage(QString("Error in DAQmxStopTask() Generation 2: %1. Aborting daq.").arg(errBuff));
    }
    if(DAQmxClearTask(taskHandle2)<0)
    {
        keep_going=0;
        DAQmxGetExtendedErrorInfo(errBuff, 2048);
        emit postSpeckleMessage(QString("Error in DAQmxClearTask() Generation 2: %1. Aborting daq.").arg(errBuff));
    }
    if(DAQmxStopTask(taskHandle_acq)<0)
    {
        keep_going=0;
        DAQmxGetExtendedErrorInfo(errBuff, 2048);
        emit postSpeckleMessage(QString("Error in DAQmxStopTask() Acquisition: %1. Aborting daq.").arg(errBuff));
    }
    if(DAQmxClearTask(taskHandle_acq)<0)
    {
        keep_going=0;
        DAQmxGetExtendedErrorInfo(errBuff, 2048);
        emit postSpeckleMessage(QString("Error in DAQmxClearTask() Acquisition: %1. Aborting daq.").arg(errBuff));
    }

    emit postSpeckleMessage(QString("daq complete"));
}
/*********************************************************************/
void DaqThread::AcquireBasicDAQ_tdmsLogging(void)
{
    int keep_going=1;
    TaskHandle  taskHandle_acq;
    int32 Wait_Time = -1;
    char errBuff[2048]={'\0'};

    // DAQmx Configure Code - Acquisition
    if(DAQmxCreateTask("",&taskHandle_acq)<0)
    {
        keep_going=0;
        DAQmxGetExtendedErrorInfo(errBuff, 2048);
        emit postSpeckleMessage(QString("Error in DAQmxCreateTask(): %1. Aborting daq.").arg(errBuff));
    }

    if(DAQmxCreateAIVoltageChan(taskHandle_acq, speckle->daq_use_ai_chan_list.toUtf8(),
        "", speckle->ai_input_config, -10.0, 10.0, DAQmx_Val_Volts, NULL)<0)
    {
        keep_going=0;
        DAQmxGetExtendedErrorInfo(errBuff, 2048);
        emit postSpeckleMessage(QString("Error in DAQmxCreateAIVoltageChan(): %1. Aborting daq.").arg(errBuff));
    }

    if(DAQmxCfgSampClkTiming(taskHandle_acq, NULL, speckle->daq_samp_rate, DAQmx_Val_Rising,
        DAQmx_Val_FiniteSamps, speckle->samples_per_channel)<0)
    {
        keep_going=0;
        DAQmxGetExtendedErrorInfo(errBuff, 2048);
        emit postSpeckleMessage(QString("Error in DAQmxCfgSampClkTiming(): %1. Aborting daq.").arg(errBuff));
    }

    // TDMS Configure Logging
    QString fname_tdms;
    fname_tdms=QString(speckle->filename+".tdms");

    //if(DAQmxConfigureLogging(taskHandle_acq,"example.tdms",DAQmx_Val_Log,"Voltage(s)",DAQmx_Val_CreateOrReplace)<0)
    if(DAQmxConfigureLogging(taskHandle_acq,fname_tdms.toUtf8(),DAQmx_Val_Log,"Voltage(s)",DAQmx_Val_CreateOrReplace)<0)
    {
        keep_going=0;
        DAQmxGetExtendedErrorInfo(errBuff, 2048);
        emit postSpeckleMessage(QString("Error in DAQmxConfigureLogging(): %1. Aborting daq.").arg(errBuff));
    }

    // DAQmx Start Code
    if(DAQmxStartTask(taskHandle_acq)<0)
    {
        keep_going=0;
        DAQmxGetExtendedErrorInfo(errBuff, 2048);
        emit postSpeckleMessage(QString("Error in DAQmxStartTask(): %1. Aborting daq.").arg(errBuff));
    }

    // now watch task and stop when task or camera is done, depending on which option has been selected
    bool32 isTaskDone;
    while(keep_going)
    {
        if(speckle->daq_status==IDLE) // daq stop button was pressed
            keep_going=0;
        else if(speckle->stop_daq_with_camera && (speckle->acquire_flag!=ACQUISITION_MODE))
            keep_going=0;
        else
        {
            DAQmxIsTaskDone (taskHandle_acq, &isTaskDone);
            if(isTaskDone)
                keep_going=0;
        }
        if(keep_going)
            msleep(20); // pause for 20ms to avoid unnecessary cpu load
    }

//    if(DAQmxWaitUntilTaskDone(taskHandle_acq,Wait_Time)<0)
//    {
//        keep_going=0;
//        DAQmxGetExtendedErrorInfo(errBuff, 2048);
//        emit postSpeckleMessage(QString("Error in DAQmxWaitUntilTaskDone() Acquisition: %1. Aborting daq.").arg(errBuff));
//    }
//    else
//        emit postSpeckleMessage(QString("Acquisition task complete."));

    // DAQmx Stop Code
    if(DAQmxStopTask(taskHandle_acq)<0)
    {
        keep_going=0;
        DAQmxGetExtendedErrorInfo(errBuff, 2048);
        emit postSpeckleMessage(QString("Error in DAQmxStopTask() Acquisition: %1. Aborting daq.").arg(errBuff));
    }
    if(DAQmxClearTask(taskHandle_acq)<0)
    {
        keep_going=0;
        DAQmxGetExtendedErrorInfo(errBuff, 2048);
        emit postSpeckleMessage(QString("Error in DAQmxClearTask() Acquisition: %1. Aborting daq.").arg(errBuff));
    }

    emit postSpeckleMessage(QString("daq complete"));
}
