<?php
$servername = "localhost";
$username = "root";
$password = "";
$dbname = "gsms";

$conn = new mysqli($servername, $username, $password, $dbname);

if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

// Fetch data from the database (replace 'your_table' with your actual table name)
$sql = "SELECT * FROM customer";
$result = $conn->query($sql);

// Check if there are rows in the result set
if ($result->num_rows > 0) {
    $rows = $result->fetch_all(MYSQLI_ASSOC);
} else {
    $rows = [];
}

$conn->close();

?>



<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" href="stylecus.css">
    <title>customer</title>
</head>
<body>
<div class="customer-container">
        <h2>Customer</h2>

        <!-- Display database table -->
        <h3>Data from Database</h3>
        <table border="1">
            <tr>
                <!-- Adjust column names based on your table structure -->
                <?php foreach ($rows[0] as $columnName => $value): ?>
                    <th><?php echo $columnName; ?></th>
                <?php endforeach; ?>
            </tr>
            <?php foreach ($rows as $row): ?>
                <tr>
                    <?php foreach ($row as $value): ?>
                        <td><?php echo $value; ?></td>
                    <?php endforeach; ?>
                </tr>
            <?php endforeach; ?>
        </table>

    <!-- Insert form -->
    <h3>Insert Data</h3>
    <form  action="insertcus.php" method="post">   
        <div class="insertcus-container">
        <div>
            <label for="cus_id">Customer ID:</label>
            <input type="text" id="cus_id" name="cus_id" required>
        </div>
        <div>
            <label for="cus_add">Customer Address:</label>
            <input type="text" id="cus_add" name="cus_add" required>
        </div>
        <div>
            <label for="cus_contact">Contact Number:</label>
            <input type="number" id="cus_contact" name="cus_contact" required>
        </div>
        <div>
            <label for="due">Due Amount:</label>
            <input type="number" id="due" name="due" step="0.01" required>
        </div>
        </div>
            
        <button class="insertbutton-container" type="submit">Insert</button>
    </form>

    <!-- Update form -->
    <h3>Update Data</h3>
    <form action="updatecus.php" method="post">
    <div class="updatecus-container">
        <div>
            <label for="cus_id">Customer ID:</label>
            <input type="text" id="cus_id" name="cus_id" required>
        </div>
        <div>
            <label for="cus_add">Customer Address:</label>
            <input type="text" id="cus_add" name="cus_add" required>
        </div>
        <div>
            <label for="cus_contact">Contact Number:</label>
            <input type="number" id="cus_contact" name="cus_contact" required>
        </div>
        <div>
            <label for="due">Due Amount:</label>
            <input type="number" id="due" name="due" step="0.01" required>
        </div>
        </div>

        <button class="updatebutton-container" type="submit">Update</button>
    </form>

    <!-- Delete form -->
    <h3>Delete Data</h3>
    <form action="deletecus.php" method="post">
        <label for="cus_id">ID:</label>
        <input type="number" id="cus_id" name="cus_id" required>
        <button class="deletebutton-container" type="submit">Delete</button>
    </form>

    <!-- Button to switch between two pages -->
        <div class="pagebutton-container">
        <form action="home.php" method="get">
            <button class="pagebuttonone-container" type="submit">Home</button>
        </form>
        <form action="index.php" method="get">
            <button class="pagebuttontwo-container" type="submit">Logout</button>
        </form>
        </div>
</div>
</body>
</html>







