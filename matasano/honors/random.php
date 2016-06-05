<?php
if(isset($_GET['Generate'])){
$rs1 = $_GET['rs1'];
$hs1 = $_GET['hs1'];
$len = $_GET['len'];
$num = $len/16 + 1;
$key = substr($hs1, 0, 32);
$seed = substr($hs1, 32, 64);
$output = "";
for($i = 0; $i < $num; $i++){
$counter = demo_counter($seed, $i);
//echo $counter;
//echo "<br>";
$output = $output .  demo_aes_e($counter, $key);
//echo $output;
//echo"<br>";
}
$output = substr($output, 0, $len*2);
$output = hex2bin($output);
}
?>
<DOCTYPE html>
<html>
 <head>
	<title> Random Demo </title>
	<script type="text/javascript" src="./main.js"></script>
	<link rel="stylesheet" href="./styles.css"></link>
</head>
<body>
	<a href="sha3.php">SHA-3 Demo</a><br>
	<a href="aes.php">AES Demo</a><br>
	<h1><u>Random Number  Demo</u></h1>
	<form action="random.php" method="get" autocomplete="off">
		<label>Seed:<br></label>
		<input maxlength="32" size="32" type="text" id="kraw" name="rs1" oninput="updateHex(this.value, 'khex')" value="<?php echo (isset($len))?$rs1:'';?>"> <br>
		<input type="text" id="khex" class="hex" name="hs1" value="<?php echo (isset($len))?$hs1:'';?>"> <br>
		<label>Length:<br></label>
		<input type="text" id="len" name="len" value="<?php echo (isset($len))?$len:'';?>"><br>
		<label>Output:<br></label>
		<h2><?php echo (isset($output))?$output:'';?></h2>
		<input type="submit" name="Generate" value="Generate">
	</form>
</body>
</html>