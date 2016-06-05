<?php
	if(isset($_GET['Hash'])){
		$input = $_GET['input'];
		$algorithm = $_GET['algorithm'];
		$len = strlen($input);
		switch($algorithm){
		case "sha224":
				$out = demo_sha3_224($input, $len);
				$out = demo_sha3_224($input, $len);
				break;
		case "sha256":
				$out = demo_sha3_256($input, $len);
				$out = demo_sha3_256($input, $len);
				break;
		case "sha384":
				$out = demo_sha3_384($input, $len);
				$out = demo_sha3_384($input, $len);
				break;
		case "sha512":
				$out = demo_sha3_512($input, $len);
				$out = demo_sha3_512($input, $len);
				break;
		}
	}
?>
<DOCTYPE html>
<html>
 <head>
	<title> SHA3 Demo </title>
	<script type="text/javascript" src="./main.js"></script>
	<link rel="stylesheet" href="./styles.css"></link>
</head>
<body>
	<h1><u>SHA3 Demo</u></h1>
	<form action="sha3.php" method="get" autocomplete="off">
	      <label>Input:<br></label>
	      <textarea name="input" rows="6" cols="16"><?php echo (isset($input))?$input:'';?></textarea><br>
	      <label>Algorithm:<label></label>
	      <select name="algorithm">
	      	      <option value="sha224">SHA-224</option>
	      	      <option value="sha256">SHA-256</option>
	      	      <option value="sha384">SHA-384</option>
	      	      <option value="sha512">SHA-512</option>
	      </select><br>
	      <input type="submit" name="Hash" value="Hash">
	</form>
	<h2><?php echo (isset($out))?$out:'';?></h2><br>
	<a href="aes.php">AES Demo</a><br>
</body>
</html>