

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
sudo mkdir -p /etc/alsa/conf.d/disabled
sudo mv /etc/alsa/conf.d/99-pulse.conf /etc/alsa/conf.d/disabled/
sudo mv /etc/alsa/conf.d/50-pulseaudio.conf /etc/alsa/conf.d/disabled/
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
nano .asoundrc
```

```bash
# Trennung von Wiedergabe und Aufnahme (asym)
pcm.!default {
    type asym
    playback.pcm "dmix_out"
    capture.pcm "dsnoop_in"
}

# Wiedergabe-Layer (Mehrere Apps gleichzeitig)
pcm.dmix_out {
    type plug
    slave {
        pcm "hw:0,0"
        rate 48000
        period_size 1024
        buffer_size 4096
    }
}

# Aufnahme-Layer (Mehrere Apps können gleichzeitig aufnehmen)
pcm.dsnoop_in {
    type plug
    slave {
        pcm "hw:0,0"
        rate 48000
        period_size 1024
        buffer_size 4096
    }
}

# WICHTIG: Direkt-Zugriff für amixer/alsamixer auf alle Regler
ctl.!default {
    type hw
    card 0
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
