#! /bin/perl
use warnings;
use strict;

sub sudoku {
    
    my ($prob) = @_;
    my %puzzle = ();

    for($i = 0; i < 81; $i++){
	my $data = substr($prob, $i, 1);
	my @pos = ($data);n
	if($data == 0){
	    @pos = (1, 2, 3, 4, 5, 6, 7, 8, 9);
	}
	$puzzle{( ($i % 9) + 1, int($i / 9) + 1)} = @pos;
    }
}
