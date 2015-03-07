#! /bin/perl -w
use strict;
use warnings;

my %lengths = (1 => 1);
sub collatz{

    my $arg = @_;
    print("$arg = arg \n");

    if(exists($lengths{$arg})){
	print("$arg exists!");
	return $lengths{$arg};

    }elsif($ $arg % 2 == 0){
	return 1 + collatz($arg / 2);
    } else {
	return 1 + collatz(3 * $arg + 1);
    }

}

my $ans = collatz(13);

print("Answer = $ans \n");
