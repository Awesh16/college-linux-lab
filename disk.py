import matplotlib.pyplot as plt

# Textbook example data
queue = [98, 183, 37, 122, 14, 124, 65, 67]
head_start = 53
cylinders = [0, 14, 37, 53, 65, 67, 98, 122, 124, 183, 199]

# --- 1. Calculate FCFS Path ---
# FCFS simply follows the order of the queue
fcfs_path = [head_start] + queue

# --- 2. Calculate SCAN Path ---
# SCAN moves towards 0 first (as assumed in the text's figure 10.6), 
# then reverses towards 199.
# Requests less than 53 (descending): 37, 14, 0 (end of disk)
# Requests greater than 53 (ascending): 65, 67, 98, 122, 124, 183
scan_path = [head_start, 37, 14, 0, 65, 67, 98, 122, 124, 183]


def plot_disk_schedule(path, title):
    """Helper function to plot the disk scheduling graph."""
    plt.figure(figsize=(10, 6))
    
    # Y-axis represents time/steps (0 is start, moving downwards)
    y_values = range(len(path))
    
    # Plot the path
    plt.plot(path, y_values, marker='o', linestyle='-', color='dodgerblue', markersize=6)
    
    # Formatting to match the textbook visual style
    plt.gca().invert_yaxis() # Invert Y axis so time flows downwards
    plt.xlim(0, 199)
    
    # Set custom X ticks to show the specific requested cylinders
    plt.xticks(cylinders, rotation=45)
    plt.yticks([]) # Hide Y-axis labels as they just represent sequence steps
    
    # Add vertical grid lines for visual tracking
    plt.grid(axis='x', linestyle='-', color='lightgrey', alpha=0.7)
    
    # Fill background color similar to the textbook
    plt.gca().set_facecolor('#e0e0e0')
    
    plt.title(title, pad=20, fontweight='bold')
    plt.xlabel('Cylinder')
    
    # Move x-axis to the top like in the textbook figures
    plt.gca().xaxis.tick_top()
    plt.gca().xaxis.set_label_position('top')
    
    plt.tight_layout()
    plt.show()

# Generate both graphs
plot_disk_schedule(fcfs_path, 'Figure 10.4: FCFS disk scheduling')
plot_disk_schedule(scan_path, 'Figure 10.6: SCAN disk scheduling')