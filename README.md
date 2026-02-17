

./uninstall.sh all wm8960 modules
```bash
git clone https://github.com/respeaker/seeed-voicecard
cd seeed-voicecard
sudo ./uninstall.sh
sudo reboot
```

```bash
with hdmi disable noaudio dtpara audio on
```


## all pi 6.y

```bash
git clone https://github.com/spookyfirehorse/wm8960-kernel-6.18.git
cd wm8960-kernel-6.18
sudo cp asound.conf /etc/
```



```bash
sudo cp wm8960-kernel-6.18/wm8960-* /boot/firmware/overlays/
```

```bash
sudo nano /boot/firmware/config.txt
```
mit camera

```bash
dtoverlay=vc4-kms-v3d,cma-512,noaudio
max_framebuffers=2
camera_auto_detect=0
dtoverlay=imx708
dtoverlay=i2s
dtparam=i2c_arm=on
dtoverlay=wm8960-soundcard
dtparam=audio=off
```

```bash
sudo systemctl disable  wm8960-soundcard.service
```

```bash
sudo nano /etc/modprobe.d/blacklist-wm8960.conf
```

```bash
blacklist snd_bcm2835
```

```bash
sudo nano /etc/modules
```

```bash
i2c-dev
snd-soc-wm8960
snd-soc-simple-card
```


```bash
sudo nano /etc/modprobe.d/allsa-base.conf
```
```bash
options snd-soc-simple-card index=0
options snd-bcm2835 index=1
options snd-usb-audio index=2
options vc4_hdmi index=3
```
```bash
sudo apt install pipewire-alsa -y
sudo apt purge pulseaudio* -y
sudo rm -r /etc/pulse
```


```bash
nano .asoundrc
```


```bash
ctl.!default {
    type pipewire
}

pcm.!default {
    type plug
    slave {
        pcm "pwire"
        format S16_LE
        rate 48000
        period_size 256
        buffer_size 1024
    }
}

pcm.pwire {
    type pipewire
    mmap_emulation 1
}
```

# for pipewire alsa

```bash
sudo sh -c 'echo "PIPEWIRE_LATENCY=512/48000" >> /etc/environment'
```
```bash
sudo nano /etc/pipewire/pipewire.conf.d/10-low-latency.conf
```
```bash
context.properties = {
    default.clock.rate          = 48000
    default.clock.quantum       = 512
    default.clock.min-quantum   = 512
    default.clock.max-quantum   = 512
}
```

```bash
sudo mkdir -p /etc/alsa/conf.d/disabled
sudo mv /etc/alsa/conf.d/99-pulse.conf /etc/alsa/conf.d/disabled/
sudo mv /etc/alsa/conf.d/50-pulseaudio.conf /etc/alsa/conf.d/disabled/
```

mmap_emulation 1 push alsa direct to pipewire

```bash
nano .asoundrc
```

```bash
ctl.!default {
    type pipewire
}

pcm.!default {
    type pipewire
    mmap_emulation 1
}
```

```bash
nano .bashrc
```
```bash
alias alsamixer='alsamixer -c 0'
alias amixer='amixer -c 0'
```

```bash
sudo reboot
```

```bash
amixer -c 0 contents | grep -A 2 "Input Mixer"
```


```bash
 sudo dmesg | grep wm8960
```

# Die Boost-Switches aktivieren die Vorverstärkung


# Haupt-Ausgangs-Mixer aktivieren (wichtig für Ton!)
```bash
amixer -c 0 sset 'Left Output Mixer PCM' on
amixer -c 0 sset 'Right Output Mixer PCM' on
```
# Kopfhörer-Lautstärke (0-127)
```bash
amixer -c 0 sset 'Headphone' 120
```
# Lautsprecher-Lautstärke (0-127)
```bash
amixer -c 0 sset 'Speaker' 120
```
# Playback-Pegel (Digitaler Master)
```bash
amixer -c 0 sset 'PCM' 200
```

# Boost-Switches für Mikrofon-Vorverstärkung (deine Befehle)

```bash
amixer -c 0 cset numid=50 on
amixer -c 0 cset numid=51 on
```
# Eingangsquelle auf Mikrofon (L/R) setzen

```bash
amixer -c 0 sset 'Left Input Mixer Boost' on
amixer -c 0 sset 'Right Input Mixer Boost' on
```
# ADC Pegel (Digitalisierung)

```bash
amixer -c 0 sset 'ADC PCM' 255
```

```bash
# Aufnahme-Lautstärke (Analog)
amixer -c 0 sset 'Capture' 63
```





```bash
amixer -c 0 cset numid=50 on
amixer -c 0 cset numid=51 on
```
```bash
# Sicherstellen, dass die ADC (Analog-Digital-Wandler) Pegel oben sind
amixer -c 0 sset 'ADC PCM' 255
amixer -c 0 sset 'Capture' 63
```
