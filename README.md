# ntab (Nice Tab)
Command line tool to prettify shell tabs

### Before
```
$ screen -ls
There are screens on:
        1234567.screen-one      (07/26/2025 04:51:58 PM)        (Detached)
        2345678.screen2 (07/26/2025 04:51:58 PM)        (Detached)
        3456789.new-screen-three        (07/26/2025 04:51:58 PM)        (Detached)
3 Sockets in /home/zac/.screen.
```

### After
```
$ screen -ls | ntab
There are screens on:
    1234567.screen-one          (07/26/2025 04:51:58 PM)    (Detached)
    2345678.screen2             (07/26/2025 04:51:58 PM)    (Detached)
    3456789.new-screen-three    (07/26/2025 04:51:58 PM)    (Detached)
3 Sockets in /home/zac/.screen.
```

### Issues

- Input is currently limited to 64000 bytes
- Tabs and the end of lines breaks the nice formatting

### Future plans
- [ ] Fix issues
- [x] Command line arg for tab size `screen -ls | ntab -t 4`

