<?php
	$conn = mysqli_connect("localhost", "root", "", "arduino");

	if (mysqli_connect_errno()) {
		die("Error connecting to database" . mysqli_connect_error());
	}
	$cm= $_GET['jarak'];
	$insert ="INSERT INTO sensor (jarak) VALUES ('$cm')";
	
	if (mysqli_query($conn, $insert)) {
		echo "Success memasukkan record";
	} else {
		echo "Error: " . $sql . "<br>" . mysqli_error($conn);
	}

?>