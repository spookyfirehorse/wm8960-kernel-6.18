

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
sudo nano /etc/modprobe.d/alsa-base.conf
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

```bash
sudo apt install pipewire-alsa rtkit
```


```bash
sudo rm -r /etc/pipewire
sudo mkdir /etc/pipewire
sudo mkdir /etc/pipewire/pipewire-pulse.conf.d
sudo mkdir /etc/pipewire/client.conf.d/
sudo mkdir /etc/pipewire/pipewire.conf.d/
sudo mkdir /etc/wireplumber
sudo mkdir /etc/wireplumber/wireplumber.conf.d/
```
```bash
sudo nano /etc/wireplumber/wireplumber.conf.d/50-alsa-s16le.conf
```

```bash
monitor.alsa.rules = [
  {
    matches = [
      {
        # Matcht alle Ausgänge
        node.name = "~alsa_output.*"
      },
      { 
        # Matcht alle Eingänge
        node.name = "~alsa_input.*"
      }
    ]
    actions = {
      update-props = {
        # Erzwingt S16LE für beide oben genannten Gruppen
        audio.format = "S16LE"
      }
    }
  }
]
```


```bash
sudo nano /etc/pipewire/pipewire.conf.d/10-low-latency.conf
```

```bash
context.properties = {
    default.clock.rate          = 48000
    default.clock.quantum       = 1024
    default.clock.min-quantum   = 1024
    default.clock.max-quantum   = 1024
}
```
# dont set it lower because audio comes to late 


# realtime

```bash
sudo nano /etc/pipewire/pipewire.conf.d/10-realtime.conf
```

```bash
context.properties = {
    default.clock.rate          = 48000
    default.clock.quantum       = 256
    default.clock.min-quantum   = 256
    default.clock.max-quantum   = 256
}
```

```bash
sudo nano /etc/enviroment
```

```bash
PIPEWIRE_LATENCY=256/48000
```

```bash
pulse.rules = [
    {
        matches = [ { application.process.binary = "rpicam-vid" } ]
        actions = {
            update-props = {
                # Erzwungenes Format
                pulse.default.format = "S16LE"
                pulse.fix.format     = "S16LE"
                audio.format         = "S16LE"

                # Berechnung für 256 Samples:
                # 256 Samples * 2 Bytes (16-Bit) * 2 Kanäle (Stereo) = 1024 Bytes  meins fragsize   4096 bei quantum 1024
                pulse.attr.fragsize = "1024"

                # PipeWire Blockgröße
                node.force-quantum = 256
            }
        }
    }
]
```

######################################
# normal kernel 

```bash
sudo rm -r /etc/pipewire
sudo mkdir /etc/pipewire
sudo mkdir /etc/pipewire/pipewire-pulse.conf.d
sudo mkdir /etc/pipewire/client.conf.d/
sudo mkdir /etc/pipewire/pipewire.conf.d/
sudo mkdir /etc/wireplumber
sudo mkdir /etc/wireplumber/wireplumber.conf.d/
```
```bash
sudo nano /etc/wireplumber/wireplumber.conf.d/50-alsa-s16le.conf
```

```bash
monitor.alsa.rules = [
  {
    matches = [
      {
        # Matcht alle Ausgänge
        node.name = "~alsa_output.*"
      },
      { 
        # Matcht alle Eingänge
        node.name = "~alsa_input.*"
      }
    ]
    actions = {
      update-props = {
        # Erzwingt S16LE für beide oben genannten Gruppen
        audio.format = "S16LE"
      }
    }
  }
]
```

```bash
sudo nano /etc/pipewire/pipewire.conf.d/10-low-latency.conf
```


```bash
context.properties = {
    default.clock.rate          = 48000
    default.clock.quantum       = 1024
    default.clock.min-quantum   = 1024
    default.clock.max-quantum   = 1024
}
```
# dont set it lower because audio comes to late 


```bash
sudo nano /etc/pipewire/client.conf.d/99-alsa-s16.conf
```

```bash
alsa.properties = {
    audio.format = "S16LE"
}
```
```bash
sudo nano /etc/pipewire/pipewire-pulse.conf.d/99-rpicam-s16.conf
```
```bash
pulse.rules = [
    {
        matches = [ { application.process.binary = "rpicam-vid" } ]
        actions = {
            update-props = {
                # Erzwungenes Format
                pulse.default.format = "S16LE"
                pulse.fix.format     = "S16LE"
                audio.format         = "S16LE"

                # Berechnung für 256 Samples:
                # 256 Samples * 2 Bytes (16-Bit) * 2 Kanäle (Stereo) = 1024 Bytes  meins fragsize   4096 bei quantum 1024
                pulse.attr.fragsize = "4096"

                # PipeWire Blockgröße
                node.force-quantum = 1024
            }
        }
    }
]
```

```bash
sudo nano /etc/enviroment
```

```bash
PIPEWIRE_LATENCY=1024/48000
```

sudo nano /etc/security/limits.d/99-realtime.conf 
```

```bash
spook  -  rtprio     99
spook  -  memlock    unlimited
spook  -  nice      -20
#*  -  rtprio     99
#*  -  memlock    unlimited
```


```bash
sudo mkdir -p /etc/alsa/conf.d/disabled
sudo mv /etc/alsa/conf.d/99-pulse.conf /etc/alsa/conf.d/disabled/
sudo mv /etc/alsa/conf.d/50-pulseaudio.conf /etc/alsa/conf.d/disabled/
```

```bash
nano .bashrc
```
# put in on the end

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

```bash
pw-top
```

```bash
pw-cli
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
