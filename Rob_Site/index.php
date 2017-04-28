<?php
	include("db.php"); 
?>
<!DOCTYPE html>
<html>
<head>
	<title></title>
	<meta http-equiv="refresh" content="5">
	<link rel="stylesheet" href="css/style.css">
</head>
<body>
	<div>
		<?php
			$info_query = "SELECT id, temp, humi, mq7, DATE(arduino.timestamp) as timecheck, arduino.timestamp as daytime FROM arduino ORDER BY id DESC LIMIT 10";
			$infores = $db->prepare($info_query);
			$infores->execute();

			echo "<div>";

			while ($row = $infores->fetch(PDO::FETCH_ASSOC)) {
				echo "<div class='main'>";
			  	echo "ID: ".$row['id']."<br>";
			  	echo "Temp: ".$row['temp']."<br>";
			  	echo "Humi: ".$row['humi']."<br>";
			  	echo "MQ7: ".$row['mq7']."<br>";
			  	echo "Timestamp: ".$row['daytime']."<br>";

		  		$day_query = "SELECT AVG(temp) as avgtemp, DATE(arduino.timestamp) as timecheck FROM arduino WHERE DATE(arduino.timestamp) = :day_check";
		  		$dayres = $db->prepare($day_query);
		  		$dayres->bindparam(':day_check', $row['timecheck']);
		  		$dayres->execute();

		  		while ($row2 = $dayres->fetch(PDO::FETCH_ASSOC)) {
		  			echo "Average temp: ".$row2['avgtemp']."<br><br>";
		  			echo "</div>";
		  		}
		  		$dayres = null;
			}

			echo "</div>";

			$infores = null;  
		?>
	</div>
</body>
</html>