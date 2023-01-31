
public class Product {
    private long code;
    private String description;
    private int quantity;

    public Product(long code, String description, int quantity) {
        this.code = code;
        this.description = description;
        this.quantity = quantity;
    }

    public long getCode() {
        return code;
    }

    public String getDescription() {
        return description;
    }

    public int getQuantity() {
        return quantity;
    }
}
