

## pi  6.18

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

```bash
sudo nano /etc/modules
```

```bash
i2c-dev
snd-soc-wm8960
```


 #  pi 6.12

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

```bash
sudo nano /etc/modules
```
```bash
i2c-dev
snd-soc-wm8960
```

```bash
#!/bin/bash

# 1. Boot-Konfiguration anpassen
echo "Konfiguriere /boot/firmware/config.txt..."
sudo tee /boot/firmware/config.txt > /dev/null <<EOF
dtoverlay=vc4-kms-v3d,cma-512,noaudio
max_framebuffers=2
camera_auto_detect=0
dtoverlay=imx708
vc4.tv_norm=PAL
dtoverlay=i2s
dtparam=i2c_arm=on
dtoverlay=wm8960-final-fix
EOF

# 2. Service deaktivieren
echo "Deaktiviere wm8960-soundcard.service..."
sudo systemctl disable wm8960-soundcard.service

# 3. Kernel-Module blacklisten
echo "Erstelle Blacklist für Module..."
sudo tee /etc/modprobe.d/blacklist-wm8960.conf > /dev/null <<EOF
blacklist snd_soc_wm8960_soundcard
blacklist snd_bcm2835
EOF

# 4. Erforderliche Module laden
echo "Aktualisiere /etc/modules..."
sudo tee /etc/modules > /dev/null <<EOF
i2c-dev
snd-soc-wm8960
EOF

echo "Fertig! Bitte starte das System mit 'sudo reboot' neu."
```






