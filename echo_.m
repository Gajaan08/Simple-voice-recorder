AudioFile = 'sound.wav'; 
[st,fs] = audioread(AudioFile);
N = fs*10; 
t = (1:fs*10)/fs;
Xt = st(1:N,1);
a=0.8;
d=2000;
y=zeros(N+d,1);
Xn=padarray(Xt,d,0,'pre');
for i=(d+1):1:N
    y(i-d)=Xt(i)+a*Xn(i-d);
end

Xf = abs(fft(Xt));
f = 1/16:1/16:fs;
figure;
plot(f(1:8*fs),Xf(1:8*fs));
title('original sound');
xlim([0 5000])
ylim([0 2000])

Yf = abs(fft(y));
f = 1/16:1/16:fs;
figure;
plot(f(1:8*fs),Yf(1:8*fs));
title('echo sound');
xlim([0 5000])
ylim([0 2000])