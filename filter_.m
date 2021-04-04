AudioFile = 'sound.wav'; 
[st,fs] = audioread(AudioFile);
N = fs*10; 
t = (1:fs*10)/fs;
Xt = st(1:N,1);
% figure;
% plot(t,Xt);
% xlabel ('Time (s)');
% ylabel ('Amplitude');
% title ('Audio Signal (Time Domain)');
Xf = abs(fft(Xt));
f = 1/16:1/16:fs;
figure;
plot(f(1:8*fs),Xf(1:8*fs));
xlabel ('Frequency (Hz)');
ylabel ('Magnitude');
title ('Audio Signal (Frequency Domain)');
xlim([0 5000])
ylim([0 2000])

%lowpass filter
lowFilt=designfilt('lowpassfir','PassbandFrequency',100,'StopbandFrequency',3500,'SampleRate',fs);
low_sig=filter(lowFilt,Xt);
%figure;
%plot(t,low_sig);
Xf1 = abs(fft(low_sig));
f = 1/16:1/16:fs;
figure;
plot(f(1:8*fs),Xf1(1:8*fs));
title ('lowpass (Frequency Domain)');
xlim([0 5000])
ylim([0 2000])

%highpass filter
highFilt=designfilt('highpassfir','PassbandFrequency', 5000,'StopbandFrequency',2500,'SampleRate',fs);
high_sig=filter(highFilt,Xt);
%figure;
%plot(t,high_sig);
Xf2 = abs(fft(high_sig));
f = 1/16:1/16:fs;
figure;
plot(f(1:8*fs),Xf2(1:8*fs));
title ('highpass (Frequency Domain)');
xlim([0 5000])
ylim([0 2000])

%bandpassfilter
bpFilt = designfilt('bandpassiir','FilterOrder',100, 'HalfPowerFrequency1',1000,'HalfPowerFrequency2',3000,'SampleRate',fs);
bp_sig=filter(bpFilt,Xt);
%figure;
%plot(t,high_sig);
Xf3 = abs(fft(bp_sig));
f = 1/16:1/16:fs;
figure;
plot(f(1:8*fs),Xf3(1:8*fs));
title ('bandpass (Frequency Domain)');
xlim([0 5000])
ylim([0 2000])

%bandstopfilter
bsFilt = designfilt('bandstopiir','FilterOrder',100, 'HalfPowerFrequency1',1000,'HalfPowerFrequency2',3000, 'SampleRate',fs);
bs_sig=filter(bsFilt,Xt);
%figure;
%plot(t,high_sig);
Xf4 = abs(fft(bs_sig));
f = 1/16:1/16:fs;
figure;
plot(f(1:8*fs),Xf4(1:8*fs));
title ('bandstop (Frequency Domain)');
xlim([0 5000])
ylim([0 2000])
