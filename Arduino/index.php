<?php
	$conn = mysqli_connect("localhost", "root", "", "penyiraman");

	if (mysqli_connect_errno()) {
		die("Error connecting to database" . mysqli_connect_error());
	}
	$status= $_GET['status'];
	$insert ="INSERT INTO stats (status) VALUES ('$status')";
	
	if (mysqli_query($conn, $insert)) {
		echo "Success memasukkan record";
	} else {
		echo "Error: " . $sql . "<br>" . mysqli_error($conn);
	}

?>
