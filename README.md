# POW
Show how much you care by adding proof of work to your messages.
Depends on the Tools submodule and also Poco libraries. Good luck compiling it.

Usage:

```
./main message.txt
```

will test 30 million nonces and save the best one to `nonce.dat`.
This can be verified by running `./verify.sh` and noting leading zeros in the hash.

LICENCE: MIT
