./uninstall.sh all wm8960 modules


```bash
6.12 vs 6.18  6.18 dtparam=audio=on dtoverlay=vc4-kms-v3d,cma-512
```

```bash
6.12 dtparam=audio=off also dtoverlay=vc4-kms-v3d,cma-512,noaudio
```

## all pi 6.18

```bash
git clone https://github.com/spookyfirehorse/wm8960-kernel-6.18.git
cd wm8960-kernel-6.18
```

```bash
sudo cp wm8960-kernel-6.18/wm8960-* /boot/firmware/overlays/
```

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
blacklist snd_soc_wm8960_soundcard
blacklist snd_bcm2835
```

```bash
sudo nano /etc/modules
```

```bash
i2c-dev
snd-soc-wm8960
```
````bash
sudo nano /etc/modprobe.d/allsa-base.conf
```

```bash
options snd-usb-audio index=-2
# WM8960 Priorität geben
options snd_soc_wm8960 index=0

# HDMI-Module auf hintere Plätze zwingen
#options snd_soc_vc4_hdmi index=1,2
#options vc4_hdmi index=1,2
```


```bash
amixer -c 0 contents | grep -A 2 "Input Mixer"
```
```bash
 sudo dmesg | grep wm8960
```
# Die Boost-Switches aktivieren die Vorverstärkung

```bash
amixer -c 0 cset numid=50 on
amixer -c 0 cset numid=51 on
```
```bash
# Sicherstellen, dass die ADC (Analog-Digital-Wandler) Pegel oben sind
amixer -c 0 sset 'ADC PCM' 255
amixer -c 0 sset 'Capture' 63
```
##########################################################################

./uninstall.sh all wm8960 modules


## all pi 6.12
```bash
git clone https://github.com/spookyfirehorse/wm8960-kernel-6.18.git
cd wm8960-kernel-6.18
```

```bash
sudo cp wm8960-kernel-6.18/wm8960-* /boot/firmware/overlays/
```

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
blacklist snd_soc_wm8960_soundcard
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
amixer -c 0 contents | grep -A 2 "Input Mixer"
```
```bash
 sudo dmesg | grep wm8960
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

# Die Boost-Switches aktivieren die Vorverstärkung


# Haupt-Ausgangs-Mixer aktivieren (wichtig für Ton!)
amixer -c 0 sset 'Left Output Mixer PCM' on
amixer -c 0 sset 'Right Output Mixer PCM' on

# Kopfhörer-Lautstärke (0-127)
amixer -c 0 sset 'Headphone' 120

# Lautsprecher-Lautstärke (0-127)
amixer -c 0 sset 'Speaker' 120

# Playback-Pegel (Digitaler Master)
amixer -c 0 sset 'PCM' 200


# Boost-Switches für Mikrofon-Vorverstärkung (deine Befehle)
amixer -c 0 cset numid=50 on
amixer -c 0 cset numid=51 on

# Eingangsquelle auf Mikrofon (L/R) setzen
amixer -c 0 sset 'Left Input Mixer Boost' on
amixer -c 0 sset 'Right Input Mixer Boost' on

# ADC Pegel (Digitalisierung)
amixer -c 0 sset 'ADC PCM' 255

# Aufnahme-Lautstärke (Analog)
amixer -c 0 sset 'Capture' 63






```bash
amixer -c 0 cset numid=50 on
amixer -c 0 cset numid=51 on
```
```bash
# Sicherstellen, dass die ADC (Analog-Digital-Wandler) Pegel oben sind
amixer -c 0 sset 'ADC PCM' 255
amixer -c 0 sset 'Capture' 63
