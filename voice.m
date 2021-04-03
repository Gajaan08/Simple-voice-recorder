AudioFile = 'sound.wav'; 
[snd,fs] = audioread(AudioFile);
N = fs*10; 
t = (1:fs*10)/fs;
Xt = snd(1:N,1);
% Time domain display
figure;
plot(t,Xt);
xlabel ('Time (s)');
ylabel ('Amplitude');
title ('Audio Signal (Time Domain)');
%Frequency domain display
Xf = abs(fft(Xt));
f = 1/16:1/16:fs;
figure;
plot(f(1:8*fs),Xf(1:8*fs));
xlabel ('Frequency (Hz)');
ylabel ('Magnitude');
title ('Audio Signal (Frequency Domain)');