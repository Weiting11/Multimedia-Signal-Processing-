% open file
data = fopen('magnitude.txt','r');
data2 = fopen('phase.txt','r');
% read data
magnitude=fread(data,'*float');
phase=fread(data2,'*float');
x=1:1:28000;
% plot
subplot(2,1,1),plot(x,magnitude);
% add label
xlabel('Frequency(Hz)');
ylabel('Magnitude(dB)');
subplot(2,1,2),plot(x,phase);
xlabel('Frequency(Hz)');
ylabel('Phase(Degree)');
% close file
fclose(data);
fclose(data2);