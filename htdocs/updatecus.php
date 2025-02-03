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
    $cusid = $_POST['cus_id'];
    $cusadd = $_POST['cus_add'];
    $cuscontact = $_POST['cus_contact'];
    $due = $_POST['due'];

    // Perform update operation
    $sql = "UPDATE customer SET due='$due',cus_add='$cusadd', cus_contact='$cuscontact' WHERE cus_id=$cusid";

    if ($conn->query($sql) === TRUE) {
        echo "Record updated successfully";
    } else {
        echo "Error updating record: " . $conn->error;
    }
}

$conn->close();
?>
