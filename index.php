<?php 

$servername = "localhost";
$username = "root";
$password = "";
$database = "mystore";

$conn = mysqli_connect($servername, $username, $password, $database);

if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
  }
  echo "Connected successfully";

  if (isset($_POST['check_product_info'])) {
    $sql = "SELECT * FROM products WHERE prod_no = 50079832";
    $result = $conn->query($sql);
  
    if ($result->num_rows > 0) {
      // output data of each row
      while($row = $result->fetch_assoc()) {
        echo $row["prod_name"];
      }
    } else {
      echo "0 results";
    }
    $conn->close();
  }

?>