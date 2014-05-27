# Universal Inject

This project allows the injection of a DLL into any process with at least one window, all without opening a handle to the process.

Code in this project is inspired by the Chinese SUPER-EC library for EasyLanguage, which contains a similar feature. This technique is commonly found in EasyLanguage-written malware.


## What exactly does this do?

* Creates a new keyboard IME, copies UInject.ime into C:\Windows\System32\ (syswow64 on 64bit-systems)
* Tells the IME what DLL we want to inject
* Sends a message to the target window to load the IME
* The IME injects the desired DLL and unloads itself.
* **TODO:** The injector uninstalls the IME.


## Projects
### Injector

handles management of the IME, deciding what and where to inject.

### UInjectIME

the IME that is installed.

### Exampledll

a dll to test injection with