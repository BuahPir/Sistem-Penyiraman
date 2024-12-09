<?php
	$conn = mysqli_connect("localhost", "root", "", "penyiraman");

	if (mysqli_connect_errno()) {
		die("Error connecting to database" . mysqli_connect_error());
	}
	$status= $_GET['status'];
	$humidity = $_GET['humidity'];
	$soil = $_GET['soil'];
	$insert ="INSERT INTO penyiraman (status, humidity, soil) VALUES ('$status','$humidity','$soil')";
	
	if (mysqli_query($conn, $insert)) {
		echo "Success memasukkan record";
	} else {
		echo "Error: " . $sql . "<br>" . mysqli_error($conn);
	}

?>