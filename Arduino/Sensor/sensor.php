<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Data Sensor</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            margin: 20px;
            background-color: #f4f4f9;
        }
        h1 {
            text-align: center;
            color: #333;
        }
        table {
            width: 80%;
            margin: 0 auto;
            border-collapse: collapse;
            background-color: #fff;
            box-shadow: 0 4px 8px rgba(0, 0, 0, 0.1);
        }
        th, td {
            border: 1px solid #ddd;
            text-align: center;
            padding: 10px;
        }
        th {
            background-color: #007BFF;
            color: white;
            font-weight: bold;
        }
        tr:nth-child(even) {
            background-color: #f9f9f9;
        }
        tr:hover {
            background-color: #f1f1f1;
        }
    </style>
</head>
<body>

<h1>Data Sensor</h1>
<?php
    $conn = mysqli_connect("localhost", "root", "", "penyiraman");

    echo "<table>";
    echo "<tr>
        <th>Nomor</th>
        <th>Status</th>
        </tr>";
    $sql = "SELECT * FROM stats";
    $qry = mysqli_query($conn, $sql);
    while ($a = mysqli_fetch_array($qry)) {
        echo "<tr>";
        echo "<td>$i.</td>";
        echo "<td>$a[status]</td>";
        echo "</tr>";
    }
    echo "</table>";
?>

</body>
</html>
