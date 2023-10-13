<?php 

$servername = "localhost";
$username = "root";
$password = "";
$database = "mystore";

$conn = mysqli_connect($servername, $username, $password, $database);

if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

if (isset($_POST['get_product_no'])) {
  $sql = "SELECT prod_no FROM products WHERE prod_no = 50079832";
  $result = $conn->query($sql);

  if ($result->num_rows > 0) {
    // output data of each row
    while($row = $result->fetch_assoc()) {
      echo $row["prod_no"];
    }
  } else {
    echo "0 results";
  }
}

if (isset($_POST['get_product_name'])) {
  $sql = "SELECT prod_name FROM products WHERE prod_no = 50079832";
  $result = $conn->query($sql);

  if ($result->num_rows > 0) {
    // output data of each row
    while($row = $result->fetch_assoc()) {
      echo $row["prod_name"];
    }
  } else {
    echo "0 results";
  }
}

if (isset($_POST['get_product_brand'])) {
  $sql = "SELECT prod_brand FROM products WHERE prod_no = 50079832";
  $result = $conn->query($sql);

  if ($result->num_rows > 0) {
    // output data of each row
    while($row = $result->fetch_assoc()) {
      echo $row["prod_brand"];
    }
  } else {
    echo "0 results";
  }
}

if (isset($_POST['get_product_price'])) {
  $sql = "SELECT prod_price FROM products WHERE prod_no = 50079832";
  $result = $conn->query($sql);

  if ($result->num_rows > 0) {
    // output data of each row
    while($row = $result->fetch_assoc()) {
      echo $row["prod_price"];
    }
  } else {
    echo "0 results";
  }
}

if (isset($_POST['get_product_promo_status'])) {
  $sql = "SELECT prod_promo_status FROM products WHERE prod_no = 50079832";
  $result = $conn->query($sql);

  if ($result->num_rows > 0) {
    // output data of each row
    while($row = $result->fetch_assoc()) {
      echo $row["prod_promo_status"];
    }
  } else {
    echo "0 results";
  }
}

if (isset($_POST['get_product_promo_price'])) {
  $sql = "SELECT prod_promo_price FROM products WHERE prod_no = 50079832";
  $result = $conn->query($sql);

  if ($result->num_rows > 0) {
    // output data of each row
    while($row = $result->fetch_assoc()) {
      echo $row["prod_promo_price"];
    }
  } else {
    echo "0 results";
  }
}

if (isset($_POST['get_product_soh'])) {
  $sql = "SELECT prod_soh FROM products WHERE prod_no = 50079832";
  $result = $conn->query($sql);

  if ($result->num_rows > 0) {
    // output data of each row
    while($row = $result->fetch_assoc()) {
      echo $row["prod_soh"];
    }
  } else {
    echo "0 results";
  }
}

?>