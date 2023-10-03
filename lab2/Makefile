root:
ifneq ($(shell id -u), 0)
	$(error You must be root)
endif

install: root
	@useradd -Mrs /bin/false trial 2> /dev/null || echo Reinstallation warning
	gcc -o trial trial.c
	install -m4755 -o trial -g trial trial /usr/bin/trial

uninstall: root
	rm -f /usr/bin/trial

purge: uninstall
	rm -f /tmp/trial
	userdel trial
