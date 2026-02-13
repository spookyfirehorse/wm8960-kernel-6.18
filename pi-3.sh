cat << 'EOF' > setup.sh
#!/bin/bash
git clone https://github.com/spookyfirehorse/wm8960-kernel-6.18.git
sudo tee /boot/firmware/config.txt > /dev/null <<EOC
dtoverlay=vc4-kms-v3d,cma-512,noaudio
max_framebuffers=2
camera_auto_detect=0
dtoverlay=imx708
vc4.tv_norm=PAL
dtoverlay=i2s
dtparam=i2c_arm=on
dtoverlay=wm8960-clock-fix
gpio=17=op,dh
EOC
sudo systemctl disable wm8960-soundcard.service 2>/dev/null
sudo tee /etc/modprobe.d/blacklist-wm8960.conf > /dev/null <<EOM
blacklist snd_soc_wm8960_soundcard
blacklist snd_bcm2835
EOM
sudo tee /etc/modules > /dev/null <<EON
i2c-dev
snd-soc-wm8960
EON
echo "Erledigt. Bitte mit 'sudo reboot' neu starten."
EOF
chmod +x setup.sh && ./setup.sh
sudo cp wm8960-kernel-6.18/wm8960-* /boot/firmware/overlays/
