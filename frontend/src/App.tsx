import { useState, useEffect } from 'react'

type Point2D = { x: number; y: number }

function App() {
  const [dark, setDark] = useState(true)
  const [width, setWidth] = useState(window.innerWidth * 0.8)
  const [height, setHeight] = useState(window.innerHeight * 0.8)
  const centerX = width / 2
  const centerY = height / 2
  const divisions = 10
  const stepX = width / divisions
  const stepY = height / divisions

  const theme = {
    bg:       dark ? '#1e1e1e' : '#ffffff',
    text:     dark ? '#ffffff' : '#111111',
    border:   dark ? '#555'    : '#ccc',
    axis:     dark ? '#888'    : '#333',
    tick:     dark ? '#888'    : '#333',
    tickText: dark ? '#aaa'    : '#333',
  }

  useEffect(() => {
    function handleResize() {
      setWidth(window.innerWidth * 0.8)
      setHeight(window.innerHeight * 0.8)
    }
    window.addEventListener('resize', handleResize)
    return () => window.removeEventListener('resize', handleResize)
  }, [])

  const [pointA, setPointA] = useState<Point2D | null>(null)
  const [pointB, setPointB] = useState<Point2D | null>(null)
  const [distance, setDistance] = useState<number | null>(null)

  async function calculateDistance() {
    const res = await fetch('http://localhost:8080/api/distance', {
      method: 'POST',
      headers: { 'Content-Type': 'application/json' },
      body: JSON.stringify({ points: [pointA, pointB] })
    })
    const data: { distance: number } = await res.json()
    setDistance(data.distance)
  }

  const xTicks = Array.from({ length: divisions - 1 }, (_, i) => ({
    svgX: stepX * (i + 1),
    label: i + 1 - divisions / 2,
  }))

  const yTicks = Array.from({ length: divisions - 1 }, (_, i) => ({
    svgY: stepY * (i + 1),
    label: divisions / 2 - (i + 1),
  }))

  return (
    <div style={{ background: theme.bg, color: theme.text, minHeight: '100vh', padding: '16px' }}>
      <div style={{ display: 'flex', alignItems: 'center', gap: '16px' }}>
        <h1>Computational Geometry</h1>
        <button onClick={() => setDark(d => !d)}>{dark ? '☀ Light' : '☾ Dark'}</button>
      </div>
      <svg
        width={width}
        height={height}
        style={{ border: `1px solid ${theme.border}`, background: theme.bg, display: 'block' }}
        onClick={(e) => {
          const rect = e.currentTarget.getBoundingClientRect()
          const svgX = e.clientX - rect.left
          const svgY = e.clientY - rect.top
          const mathX = (svgX - centerX) / stepX
          const mathY = -(svgY - centerY) / stepY
          if (!pointA) {
            setPointA({ x: mathX, y: mathY })
          } else if (!pointB) {
            setPointB({ x: mathX, y: mathY })
          }
        }}
      >
        {/* Axes */}
        <line x1={0} y1={centerY} x2={width} y2={centerY} stroke={theme.axis} />
        <line x1={centerX} y1={0} x2={centerX} y2={height} stroke={theme.axis} />

        {/* X-axis ticks and labels */}
        {xTicks.map(({ svgX, label }) => (
          <g key={`x-${label}`}>
            <line x1={svgX} y1={centerY - 5} x2={svgX} y2={centerY + 5} stroke={theme.tick} />
            {label !== 0 && (
              <text x={svgX} y={centerY + 18} textAnchor="middle" fontSize={11} fill={theme.tickText}>{label}</text>
            )}
          </g>
        ))}

        {/* Y-axis ticks and labels */}
        {yTicks.map(({ svgY, label }) => (
          <g key={`y-${label}`}>
            <line x1={centerX - 5} y1={svgY} x2={centerX + 5} y2={svgY} stroke={theme.tick} />
            {label !== 0 && (
              <text x={centerX - 8} y={svgY + 4} textAnchor="end" fontSize={11} fill={theme.tickText}>{label}</text>
            )}
          </g>
        ))}

        {pointA && (
          <g>
            <circle cx={pointA.x * stepX + centerX} cy={-pointA.y * stepY + centerY} r={5} fill="royalblue" />
            <text x={pointA.x * stepX + centerX + 8} y={-pointA.y * stepY + centerY} fontSize={12} fill={theme.text}>A</text>
          </g>
        )}
        {pointB && (
          <g>
            <circle cx={pointB.x * stepX + centerX} cy={-pointB.y * stepY + centerY} r={5} fill="tomato" />
            <text x={pointB.x * stepX + centerX + 8} y={-pointB.y * stepY + centerY} fontSize={12} fill={theme.text}>B</text>
          </g>
        )}
      </svg>
      {pointA && pointB && (
        <button onClick={calculateDistance}>Calculate Distance</button>
      )}
      {distance !== null && <p>Distance: {distance.toFixed(2)}</p>}
    </div>
  )
}

export default App
