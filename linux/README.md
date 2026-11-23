# linux cheatsheet

```bash
# get info on your device first
# sdb           8:16   1  29,6G  0 disk 
# └─sdb1        8:17   1  29,6G  0 part /path/to/device
```
```bash
lsblk
```

```bash
# if mounted: umount
# sdb           8:16   1  29,6G  0 disk 
# └─sdb1        8:17   1  29,6G  0 part
```
```bash
sudo umount /dev/sdX1
```

```bash
# for fat32
```
```bash
sudo mkfs.vfat -F 32 -n MY_USB /dev/sdX1
```

```bash
# for exfat
```
```bash
sudo mkfs.exfat -n MY_USB /dev/sdX1
```

```bash
# for ext4
```
```bash
sudo mkfs.ext4 -L MY_USB /dev/sdX1
```

```bash
# mount it again if needed
```
```bash
sudo mount /dev/sdb1 /path/to/device
```
