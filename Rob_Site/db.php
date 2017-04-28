<?php
	$servername = "82.148.66.15";
	$database = "2509972569_robtest";
	$username = "2509972569";
	$password = "mypassword";

	try {
		$db = new PDO("mysql:host=$servername;dbname=$database", $username, $password);
		$db->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
	} catch (Exception $e) {
		echo "Connection failed! ".$e->getMessage();
	}
?>