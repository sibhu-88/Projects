# Body Control Module (BCM) in Automobiles

This project demonstrates the implementation of a Body Control Module (BCM) using CAN (Controller Area Network) communication with ARM microcontrollers. The BCM is responsible for controlling the left and right indicators and the wiper system in a vehicle. The system involves a network of four nodes, where one node acts as the transmitter and the remaining three nodes act as receivers.

## Objectives

- Implement CAN communication between nodes.
- Transmit and receive data frames using the CAN protocol.
- Control vehicle indicators and wipers based on CAN messages.
- Display relevant information via UART and LCD interfaces.

## Required Equipment

- ARM microcontroller development boards (4 units)
- CAN transceivers (4 units)
- Switches (3 units for the transmitter node)
- LEDs (for indicating left and right indicators)
- Motor or servo (for the wiper control)
- LCD display module
- UART communication module
- Connecting wires
- Power supply

## System Overview

The system comprises four nodes:

1. **Node A (Transmitter)**: Monitors the state of switches and sends CAN messages to the receiver nodes.
2. **Node B (Receiver)**: Controls the right indicator based on received CAN messages.
3. **Node C (Receiver)**: Controls the left indicator based on received CAN messages.
4. **Node D (Receiver)**: Controls the wiper based on received CAN messages.

## Project Steps

### Step 1: Setup Hardware

1. **Assemble the Nodes**:
    - Connect CAN transceivers to each ARM microcontroller development board.
    - Connect switches to the transmitter node (Node A).
    - Connect LEDs to Node B and Node C for right and left indicators, respectively.
    - Connect a motor or servo to Node D for the wiper control.
    - Connect an LCD display and UART communication module to Node A.
2. **Power Supply**:
    - Ensure all nodes have a reliable power supply.

### Step 2: Implement CAN Communication

1. **Initialize CAN Transceivers**:
    - Configure CAN transceivers on each node.
    - Set up the CAN baud rate and other necessary settings.
2. **Develop CAN Protocol**:
    - Define the CAN message structure.
    - Implement CAN message sending functionality in Node A.
    - Implement CAN message receiving functionality in Nodes B, C, and D.

### Step 3: Program Each Node

1. **Node A (Transmitter)**:
    - Monitor the state of switches.
    - Send appropriate CAN messages based on the switch status.
    - Display status messages on the LCD and via UART.
2. **Node B (Right Indicator Receiver)**:
    - Receive CAN messages.
    - Control the right indicator LED based on the received messages.
3. **Node C (Left Indicator Receiver)**:
    - Receive CAN messages.
    - Control the left indicator LED based on the received messages.
4. **Node D (Wiper Receiver)**:
    - Receive CAN messages.
    - Control the wiper motor or servo based on the received messages.

### Step 4: Testing and Debugging

1. **Test Individual Nodes**:
    - Test each node independently to ensure correct functionality.
2. **Test Communication**:
    - Test the CAN communication between nodes.
    - Verify that Node A correctly sends messages and that Nodes B, C, and D correctly receive and act on these messages.
3. **Debug Issues**:
    - Use debugging tools to identify and fix any issues in the communication or control logic.

### Step 5: Final Integration

1. **Integrate All Nodes**:
    - Connect all nodes together via the CAN bus.
    - Ensure proper communication and control across all nodes.
2. **Final Testing**:
    - Conduct comprehensive testing to ensure the entire system works as expected.
    - Make any necessary adjustments based on test results.

## Conclusion

This project successfully demonstrates the use of the CAN protocol for communication between nodes in an embedded system. The system is capable of transmitting and receiving data frames, controlling external devices, and providing feedback through UART and LCD interfaces. This implementation can be further expanded for more complex applications in automotive and industrial systems.
