<h1>Data Sensor</h1>
<?php
    $conn = mysqli_connect("localhost", "root","","arduino");

    echo "<table border='1' cellpadding='5'cellspacing='0' >";
    echo "<tr>
        <td>Nomor</td>
        <td>Jarak</td>
        <td>Checkpoint</td>
        </tr>";
    $sql = "SELECT * FROM sensor ORDER by jarak DESC";
    $qry = mysqli_query($conn, $sql);
    $i = 1;
    while ($a = mysqli_fetch_array($qry)) {
        echo "<tr>";
        echo "<td>$i.</td>";
        echo "<td>$a[jarak]</td>";
        echo "<td>Checkpoint $i</td>";
        echo "</tr>";
        $i++;
}
echo "</table>";
?>
