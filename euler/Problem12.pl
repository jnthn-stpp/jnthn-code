#! /bin/perl -w

sub factors {
my ($num) = @_;
@ans = ();

for($i = 1; $i <= sqrt($num); $i++){
    if($num % $i == 0){
	$j = $num / $i;
	#print("Factors: $i, $j\n");
	
	push(@ans, $i);
	if($i != $j){
	push(@ans, $j);
	}
    }
}

    return sort(@ans);
}

$tri = 1;
$nxt = 1;
@facts = (1);
$length = 1;

while($length < 500){
   print("Tri: $tri, Length: $length \n");
    $nxt += 1;
    $tri += $nxt;

    @facts = factors($tri);
    $length = @facts;
}

print("Answer $tri\n");

foreach $i (@facts){
    print("$i, ");

}
print("\nLength: $length \n");
