# WM8960 Audio HAT

The drivers of [WM8960 Audio HAT] for Raspberry Pi.

http://www.waveshare.net/shop/WM8960-Audio-HAT.htm

http://www.waveshare.com/wm8960-audio-hat.htm

## pi4 6.12

```bash
sudo nano /boot/firmware/config.txt
dtoverlay=vc4-kms-v3d,cma-512,noaudio
max_framebuffers=2
camera_auto_detect=0
dtoverlay=imx708
vc4.tv_norm=PAL
dtoverlay=i2s
dtparam=i2c_arm=on
dtoverlay=wm8960-soundcard
```

```bash
sudo nano /etc/modules
```
```bash
i2c-dev
snd-soc-wm8960
```

```bash
sudo nano /etc/modprobe.d/blacklist-wm8960.conf
```

```bash
blacklist snd_soc_wm8960_soundcard
blacklist snd_bcm2835
```

```bash
sudo systemctl disable  wm8960-soundcard.service
```
## pi4 6.18

```bash
sudo nano /boot/firmware/config.txt
```

```bash
dtoverlay=vc4-kms-v3d,cma-512,noaudio
max_framebuffers=2
camera_auto_detect=0
dtoverlay=imx708
vc4.tv_norm=PAL
dtoverlay=i2s
dtparam=i2c_arm=on
dtoverlay=wm8960-final-fix
```

```bash
sudo systemctl disable  wm8960-soundcard.service
```

```bash
sudo nano /etc/modprobe.d/blacklist-wm8960.conf
```

```bash
blacklist snd_soc_wm8960_soundcard
blacklist snd_bcm2835
```

 #  pi3 6.12

```bash
sudo nano /boot/firmware/config.txt
```

```bash
dtoverlay=vc4-kms-v3d,cma-512,noaudio
max_framebuffers=2
camera_auto_detect=0
dtoverlay=imx708
vc4.tv_norm=PAL
dtoverlay=i2s
dtparam=i2c_arm=on
dtoverlay=wm8960-clock-fix
gpio=17=op,dh
```

```bash
sudo systemctl disable  wm8960-soundcard.service
```

```bash
sudo nano /etc/modprobe.d/blacklist-wm8960.conf
```

```bash
blacklist snd_soc_wm8960_soundcard
blacklist snd_bcm2835
```









