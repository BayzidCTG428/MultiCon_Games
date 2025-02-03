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
    $supid = $_POST['sup_id'];
    $supcom = $_POST['sup_com'];
    $supcontact = $_POST['sup_contact'];
    $suplocation = $_POST['sup_location'];

    // Perform update operation
    $sql = "UPDATE suppliers SET sup_contact='$supcontact',sup_location='$suplocation', sup_com='$supcom' WHERE sup_id='$supid'";

    if ($conn->query($sql) === TRUE) {
        echo "Record updated successfully";
    } else {
        echo "Error updating record: " . $conn->error;
    }
}

$conn->close();
?>
