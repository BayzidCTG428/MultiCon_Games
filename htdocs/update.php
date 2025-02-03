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

    // Perform update operation
    $sql = "UPDATE inventory SET selling_price='$sellp',pro_cat='$procat', doe='$date' WHERE pro_id=$proid";

    if ($conn->query($sql) === TRUE) {
        echo "Record updated successfully";
    } else {
        echo "Error updating record: " . $conn->error;
    }
}

$conn->close();
?>
