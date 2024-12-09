<?php
$conn = mysqli_connect("localhost", "root", "", "penyiraman");

// Periksa koneksi database
if (mysqli_connect_errno()) {
    die("Error connecting to database: " . mysqli_connect_error());
}

// Ambil data terakhir
$sql = "SELECT * FROM penyiraman ORDER BY id DESC LIMIT 1"; // Ambil data terakhir berdasarkan urutan ID
$qry = mysqli_query($conn, $sql);
$a = mysqli_fetch_assoc($qry);

// Tampilkan data dalam tabel
if ($a) {
    echo "<table border='1' cellpadding='5' cellspacing='0'>";
    echo "<tr>
        <th>Nomor</th>
        <th>Status</th>
        <th>Humidity (%)</th>
        <th>Soil Moisture (%)</th>
        <th>Waktu Sekarang</th>
        </tr>";
    echo "<tr>";
    echo "<td>1.</td>";
    echo "<td>" . htmlspecialchars($a['status']) . "</td>"; // Hindari XSS
    echo "<td>" . htmlspecialchars($a['humidity']) . "</td>";
    echo "<td>" . htmlspecialchars($a['soil']) . "</td>";
    echo "<td>" . date("Y-m-d H:i:s") . "</td>"; // Ambil waktu saat ini
    echo "</tr>";
    echo "</table>";
} else {
    echo "Tidak ada data.";
}

// Tutup koneksi database
mysqli_close($conn);
?>
