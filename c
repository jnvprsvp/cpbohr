<!DOCTYPE html>
<html>
<head>
  <title>Bohr Diagram ()</title>
  <style>
    body { font-family: sans-serif; padding: 20px; }
    canvas { border: 1px solid #ccc; margin-top: 10px; }
    #configOutput { margin-top: 15px; font-family: monospace; }
  </style>
</head>
<body>
  <h2>Bohr Diagram Generator</h2>
  <label>Atomic Number:</label>
  <input type="number" id="atomicNumber" min="1" max="158" />
  <button onclick="drawBohr()">Draw</button>

  <canvas id="bohrCanvas" width="600" height="600"></canvas>

  <div id="configOutput"></div>

  <script>
    const orbitals = [
      { n: 1, l: 0, name: "1s", capacity: 2 },
      { n: 2, l: 0, name: "2s", capacity: 2 },
      { n: 2, l: 1, name: "2p", capacity: 6 },
      { n: 3, l: 0, name: "3s", capacity: 2 },
      { n: 3, l: 1, name: "3p", capacity: 6 },
      { n: 4, l: 0, name: "4s", capacity: 2 },
      { n: 3, l: 2, name: "3d", capacity: 10 },
      { n: 4, l: 1, name: "4p", capacity: 6 },
      { n: 5, l: 0, name: "5s", capacity: 2 },
      { n: 4, l: 2, name: "4d", capacity: 10 },
      { n: 5, l: 1, name: "5p", capacity: 6 },
      { n: 6, l: 0, name: "6s", capacity: 2 },
      { n: 4, l: 3, name: "4f", capacity: 14 },
      { n: 5, l: 2, name: "5d", capacity: 10 },
      { n: 6, l: 1, name: "6p", capacity: 6 },
      { n: 7, l: 0, name: "7s", capacity: 2 },
      { n: 5, l: 3, name: "5f", capacity: 14 },
      { n: 6, l: 2, name: "6d", capacity: 10 },
      { n: 7, l: 1, name: "7p", capacity: 6 },
      { n: 8, l: 0, name: "8s", capacity: 2 },
      { n: 5, l: 4, name: "5g", capacity: 18 },
      { n: 6, l: 3, name: "6f", capacity: 14 },
      { n: 7, l: 2, name: "7d", capacity: 10 },
      { n: 8, l: 1, name: "8p", capacity: 6 },
    ];

    // Sort orbitals by n + l rule
    orbitals.sort((a, b) => {
      const sumA = a.n + a.l;
      const sumB = b.n + b.l;
      return sumA === sumB ? a.n - b.n : sumA - sumB;
    });

    function drawBohr() {
      const Z = parseInt(document.getElementById("atomicNumber").value);
      if (isNaN(Z) || Z < 1 || Z > 158) {
        alert("Enter an atomic number between 1 and 158.");
        return;
      }

      const canvas = document.getElementById("bohrCanvas");
      const ctx = canvas.getContext("2d");
      ctx.clearRect(0, 0, canvas.width, canvas.height);

      const shellElectrons = {};
      let remaining = Z;
      let configStr = "";

      for (const orb of orbitals) {
        if (remaining <= 0) break;
        const fill = Math.min(orb.capacity, remaining);
        remaining -= fill;

        // Build configuration string
        if (fill > 0) configStr += `${orb.name}^${fill} `;

        // Count electrons per shell for Bohr diagram
        if (!shellElectrons[orb.n]) shellElectrons[orb.n] = 0;
        shellElectrons[orb.n] += fill;
      }

      // Draw nucleus
      const centerX = canvas.width / 2;
      const centerY = canvas.height / 2;
      const orbitGap = 30;

      ctx.fillStyle = "gray";
      ctx.beginPath();
      ctx.arc(centerX, centerY, 10, 0, 2 * Math.PI);
      ctx.fill();

      // Draw shells and electrons
      const shellNumbers = Object.keys(shellElectrons).map(Number).sort((a, b) => a - b);
      for (let i = 0; i < shellNumbers.length; i++) {
        const n = shellNumbers[i];
        const count = shellElectrons[n];
        const radius = orbitGap * n;

        // Orbit ring
        ctx.strokeStyle = "black";
        ctx.beginPath();
        ctx.arc(centerX, centerY, radius, 0, 2 * Math.PI);
        ctx.stroke();

        // Electrons on ring
        for (let j = 0; j < count; j++) {
          const angle = (2 * Math.PI / count) * j;
          const x = centerX + radius * Math.cos(angle);
          const y = centerY + radius * Math.sin(angle);
          ctx.fillStyle = "blue";
          ctx.beginPath();
          ctx.arc(x, y, 4, 0, 2 * Math.PI);
          ctx.fill();
        }
      }

      // Show electron configuration
      document.getElementById("configOutput").textContent =
        `Electron Configuration: ${configStr.trim()}`;
    }
  </script>
</body>
</html>
