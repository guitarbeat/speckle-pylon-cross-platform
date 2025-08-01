% writes data in variable cmap to variable in c header file
% assumes that cmap has been loaded or otherwise generated
fname = 'greens_colormap.h';
c_variable_name = 'greens_colormap1D';

% convert cmap to 0-255 range
load Greens.mat
cmap = round(cmap*256);
cmap = cmap'; % make it write values in correct order

fp=fopen(fname, 'w');
fprintf(fp, 'unsigned char %s[%i]= {\n', c_variable_name, length(cmap(:)));
for i=1:length(cmap(:))-1
    fprintf(fp, '%i,\n', cmap(i));
end
fprintf(fp, '%i};', cmap(i+1));
fclose(fp);
