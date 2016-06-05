<?php
if(isset($_GET['Encrypt'])){
$rawkey = $_GET['rawkey'];
$hexkey = $_GET['hexkey'];
$rawin = $_GET['rawin'];
$hexin = $_GET['hexin'];
$output = demo_aes_e($hexin, $hexkey);
$rawout = hex2bin($output);
} elseif(isset($_GET['Decrypt'])){
$rawkey = $_GET['rawkey'];
$hexkey = $_GET['hexkey'];
$hexin = $_GET['hexin'];
$rawin = hex2bin($hexin);
$output = demo_aes_d($hexin, $hexkey);
$rawout = hex2bin($output);
} elseif(isset($_GET['rawkey'])){
$rawkey = $_GET['rawkey'];
$hexkey = $_GET['hexkey'];
$hexin = $_GET['hexin'];
$rawin = hex2bin($hexin);
}
?>
<DOCTYPE html>
<html>
 <head>
	<title> AES Demo </title>
	<script type="text/javascript" src="./main.js"></script>
	<link rel="stylesheet" href="./styles.css"></link>
</head>
<body>
	<a href="sha3.php">SHA-3 Demo</a><br>
	<h1><u>AES-128 Demo</u></h1>
	<form action="aes.php" method="get" autocomplete="off">
		<label>Key:<br></label>
		<input maxlength="16" size="16" type="text" id="kraw" name="rawkey" oninput="updateHex(this.value, 'khex')" value="<?php echo (isset($rawkey))?$rawkey:'';?>"> <br>
		<input type="text" id="khex" class="hex" name="hexkey" value="<?php echo (isset($rawkey))?$hexkey:'';?>"> <br>
		<label>Plain Text:<br></label>
		<input maxlength="16" type="text" id="iraw" name="rawin" oninput="updateHex(this.value, 'ihex')" value="<?php echo (isset($rawkey))?$rawin:'';?>"> <br>
		<input type="text" id="ihex" class="hex" name="hexin" value="<?php echo (isset($rawkey))?$hexin:'';?>"> <br>
		<label>Cipher Text:<br></label>
		<h2><?php echo (isset($output))?$output:'';?></h2>
		<h2><?php echo (isset($output))?$rawout:'';?></h2>
		<input type="submit" name="Encrypt" value="Encrypt">
		<input type="submit" name="Decrypt" value="Decrypt">
	</form>
</body>
</html>