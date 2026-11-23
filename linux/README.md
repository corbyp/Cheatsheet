# linux cheatsheet

```bash
# get info on your device first
lsblk
# sdb           8:16   1  29,6G  0 disk 
# └─sdb1        8:17   1  29,6G  0 part /path/to/device
```

```bash
# if mounted: umount
sudo umount /dev/sdX1
# sdb           8:16   1  29,6G  0 disk 
# └─sdb1        8:17   1  29,6G  0 part
```

```bash
# for fat32
sudo mkfs.vfat -F 32 -n MY_USB /dev/sdX1
```

```bash
# for exfat
sudo mkfs.exfat -n MY_USB /dev/sdX1
```

```bash
# for ext4
sudo mkfs.ext4 -L MY_USB /dev/sdX1
```

```bash
# mount it again if needed
sudo mount /dev/sdb1 /path/to/device
```
