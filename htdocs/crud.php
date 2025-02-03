<?php
session_start();

// Check if the user is logged in
if (!isset($_SESSION['username'])) {
    header("Location: index.php");
    exit();
}

// Include database connection code here

// Perform CRUD operations based on the 'page' parameter
$page = isset($_GET['page']) ? $_GET['page'] : 'insert';

switch ($page) {
    case 'insert':
        // Insert data logic
        break;
    case 'update':
        // Update data logic
        break;
    case 'delete':
        // Delete data logic
        break;
    default:
        // Handle invalid page
        break;
}
?>

<!-- HTML content for CRUD operations -->
