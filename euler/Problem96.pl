#! /bin/perl
use warnings;
use strict;

sub setUpPuzzle {

    my ($prob) = @_;
    my @puzzle = ();

    for(my $i = 0; $i < 81; $i++){
	my $data = substr($prob, $i, 1);
	my @pos = ($data);
	if($data == 0){
	    @pos = (1..9);
	}
	$puzzle[$i] = \@pos;
    }
    return @puzzle;
}

sub coord {
    my ($x, $y) = @_;

    return ($x - 1) + (9 * ($y - 1));
}

sub simplify {
    my ($x, $y) = @_;
}
my @array = setUpPuzzle("003020600900305001001806400008102900700000008006708200002609500800203009005010300");

my $num = $array[coord(1, 2)]->[0];
my $len = $array[coord(3, 1)];

print "\nnum:\t$num \n"
