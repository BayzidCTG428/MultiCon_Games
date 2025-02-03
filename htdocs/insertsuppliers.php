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

    // Perform insert operation
    $sql = "INSERT INTO suppliers (sup_id, sup_com, sup_contact, sup_location) VALUES ('$supid', '$supcom','$supcontact', '$suplocation')";

    if ($conn->query($sql) === TRUE) {
        echo "Record inserted successfully";
    } else {
        echo "Error: " . $sql . "<br>" . $conn->error;
    }
}

$conn->close();
?>
