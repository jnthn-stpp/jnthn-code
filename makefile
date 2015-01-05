all : euler-p jnthn-p

euler-p : jnthn
	cd euler; make

jnthn-p :
	cd jnthn; make
