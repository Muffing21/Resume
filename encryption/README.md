#How to use the program?

### keygen: 
###-b: specifies the minimum bits needed for the public modulus n
###-i: specifies the number of Miller-Rabin iterations for testing primes (default: 50)
###-n: pbfile: specifies the public key file (default: rsa.pub)
###-d: pvfile: specifies the private key file (default: rsa.priv)
###-s: specifies the random seed for the random state initialization (default: the seconds since the unix epoch, given time(NULL))
###-v: enables verbose output
###-h: displays program synopsis and usage

###./keygen -b (some num bits) -i (some num iter) -n (some pbfile) -d (some pvfile) -s (seed) -v -h

### if you didn't input anything then it will resort to default numbers in the program

### encrypt:
#-i: specifies the number of Miller-Rabin iterations for testing primes (default: 50)
#-o: specifies the output file to encrypt (default: stdout)
#-n: pbfile: specifies the public key file (default: rsa.pub)
#-v: enables verbose output
#-h: displays program synopsis and usage

###./encrypt -i test.txt -o test_out.txt

# decrypt:

### same thing as encrypt

### ./decrypt -i test_out.txt -o test_out.txt

###no complaints from scanbuild

### make clean
### make format
### make

