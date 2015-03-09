#! /bin/perl -w
use strict;
use warnings;

my %lengths = (1 => 1);
sub collatz{

    my ($arg) = @_;
    #print("$arg = arg \n");

    if(exists($lengths{$arg})){
	#print("$arg exists!");
	return $lengths{$arg};

    }elsif(($arg % 2) == 0){
	my $temp = 1 + collatz($arg / 2);
	$lengths{$arg} = $temp;
	return $temp;
    } else {
	my $temp = 1 + collatz(3 * $arg + 1);
	$lengths{$arg} = $temp;
	return $temp;
    }

}

my $ans = 1;

for(my $i = 2; $i <= 1000000; $i++){

    my $temp = collatz($i);
    if($temp > $ans){
	$ans = $temp;
    }
}
