<?php
session_start();

// Check if the user is logged in
if (!isset($_SESSION["loggedin"]) || $_SESSION["loggedin"] !== true) {
    header("Location: index.php");
    exit;
}
?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" href="style.css">
    <title>Dashboard</title>
</head>
<body>
    <h1>Welcome, Admin!</h1>
    <ul>
        <li><a href="insert.php">Insert Item</a></li>
        <li><a href="update.php">Update Item</a></li>
        <li><a href="delete.php">Delete Item</a></li>
        <!-- Add more pages as needed -->
    </ul>
    <a href="logout.php">Logout</a>
</body>
</html>
<?php
session_start();

// Check if the user is logged in
if (!isset($_SESSION['username'])) {
    header("Location: index.php");
    exit();
}
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" href="style.css">
    <title>Dashboard</title>
</head>
<body>
    <div class="dashboard-container">
        <h2>Dashboard</h2>

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
    </div>
</body>
</html>
