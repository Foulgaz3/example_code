import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns

def parse_simulation(file_path):
    bodies_data = []
    motion_data = []
    stepsize = None
    
    # Flags to identify sections
    bodies_section = False
    motion_section = False
    
    # Open and read the file line by line
    with open(file_path, 'r') as file:
        for line in file:
            line = line.strip()
            if line == 'BODIES':
                bodies_section = True
                motion_section = False
            elif line == 'MOTION':
                bodies_section = False
                motion_section = True
            elif line.startswith('STEPSIZE:'):
                stepsize = float(line.split()[1])
            elif bodies_section and line:
                if not line.startswith('id'):  # Skip the header line
                    bodies_data.append(line.split(', '))
            elif motion_section and line:
                if not line.startswith('timestep'):  # Skip the header line
                    motion_data.append(line.split(', '))
    
    # Create DataFrames from the collected data
    bodies_df = pd.DataFrame(bodies_data, columns=['id', 'mass', 'x', 'y', 'Vx', 'Vy', 'moves'])
    motion_df = pd.DataFrame(motion_data, columns=['timestep', 'id', 'x', 'y', 'Vx', 'Vy'])
    
    # Convert appropriate columns to numeric types
    bodies_df = bodies_df.apply(pd.to_numeric)
    motion_df = motion_df.apply(pd.to_numeric)
    return bodies_df, motion_df, stepsize


if __name__ == "__main__":
    path = 'build/simulation.txt'
    
    planets, motion, stepsize = parse_simulation(path)
    print(planets.head().to_string())
    print(motion.head().to_string())
    print(f"seconds per timestep: {stepsize}")
    
    sns.scatterplot(motion , x='x', y='y', hue='id', s=5)

plt.savefig("graph.png")