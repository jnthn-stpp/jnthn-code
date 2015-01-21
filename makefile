all : jnthn-p euler-p

euler-p : jnthn-p
	cd euler; make

jnthn-p :
	cd jnthn; make
