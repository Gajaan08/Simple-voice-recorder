AudioFile = 'sound.wav'; 
[st,fs] = audioread(AudioFile);
N = fs*10; 
t = (1:fs*10)/fs;
Xt = st(1:N,1);
figure1=figure('Position', [400, 400, 1600, 2000]);
subplot(5,2,1);
plot(t,Xt);
xlabel ('Time (s)');
ylabel ('Amplitude');
title ('Audio Signal (Time Domain)');
Xf = abs(fft(Xt));
f = 1/16:1/16:fs;

subplot(5,2,2);
plot(f(1:8*fs),Xf(1:8*fs));
xlabel ('Frequency (Hz)');
ylabel ('Magnitude');
title ('Audio Signal (Frequency Domain)');
xlim([0 5000])
ylim([0 1500])

%lowpass filter
lowFilt=designfilt('lowpassfir','PassbandFrequency',100,'StopbandFrequency',3500,'SampleRate',fs);
low_sig=filter(lowFilt,Xt);

subplot(5,2,3);
plot(t,low_sig);
title ('lowpass (Time Domain)');
Xf1 = abs(fft(low_sig));
f = 1/16:1/16:fs;

subplot(5,2,4);
plot(f(1:8*fs),Xf1(1:8*fs));
title ('lowpass (Frequency Domain)');
xlim([0 5000])
ylim([0 1500])

%highpass filter
highFilt=designfilt('highpassfir','PassbandFrequency', 5000,'StopbandFrequency',2500,'SampleRate',fs);
high_sig=filter(highFilt,Xt);

subplot(5,2,5);
plot(t,high_sig);
title ('highpass (Time Domain)');
Xf2 = abs(fft(high_sig));
f = 1/16:1/16:fs;

subplot(5,2,6);
plot(f(1:8*fs),Xf2(1:8*fs));
title ('highpass (Frequency Domain)');
xlim([0 5000])
ylim([0 1500])

%bandpassfilter
bpFilt = designfilt('bandpassiir','FilterOrder',100, 'HalfPowerFrequency1',1000,'HalfPowerFrequency2',3000,'SampleRate',fs);
bp_sig=filter(bpFilt,Xt);

subplot(5,2,7);
plot(t,bp_sig);
title ('bandpass (Time Domain)');
Xf3 = abs(fft(bp_sig));
f = 1/16:1/16:fs;

subplot(5,2,8);
plot(f(1:8*fs),Xf3(1:8*fs));
title ('bandpass (Frequency Domain)');
xlim([0 5000])
ylim([0 1500])

%bandstopfilter
bsFilt = designfilt('bandstopiir','FilterOrder',100, 'HalfPowerFrequency1',1000,'HalfPowerFrequency2',3000, 'SampleRate',fs);
bs_sig=filter(bsFilt,Xt);

subplot(5,2,9);
plot(t,bs_sig);
title ('Bandstop (Time Domain)');
Xf4 = abs(fft(bs_sig));
f = 1/16:1/16:fs;

subplot(5,2,10);
plot(f(1:8*fs),Xf4(1:8*fs));
title ('bandstop (Frequency Domain)');
xlim([0 5000])
ylim([0 1500])
