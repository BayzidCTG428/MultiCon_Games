<?php
// Include database connection code here
$servername = "localhost";
$username = "root";
$password = "";
$dbname = "gsms";

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);

// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

// Handle form submission
if ($_SERVER["REQUEST_METHOD"] == "POST") {
    // Retrieve form data
    $proid = $_POST['pro_id'];
    $procat = $_POST['pro_cat'];
    $date = $_POST['doe'];
    $sellp = $_POST['selling_price'];

    // Perform insert operation
    $sql = "INSERT INTO inventory (pro_id, pro_cat, doe, selling_price) VALUES ('$proid', '$procat','$date', '$sellp')";

    if ($conn->query($sql) === TRUE) {
        echo "Record inserted successfully";
    } else {
        echo "Error: " . $sql . "<br>" . $conn->error;
    }
}

$conn->close();
?>
