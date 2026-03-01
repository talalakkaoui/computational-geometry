import { useState } from 'react'

function App() {
  const [pointA, setPointA] = useState(null)
  const [pointB, setPointB] = useState(null)
  const [distance, setDistance] = useState(null)
  console.log('Point A:', pointA)
  console.log('Point B:', pointB)
  async function calculateDistance() {
  const res = await fetch('http://localhost:8080/api/distance', {
    method: 'POST',
    headers: { 'Content-Type': 'application/json' },
    body: JSON.stringify({ points: [pointA, pointB] })
  })
  const data = await res.json()
  setDistance(data.distance)
}


  return (
<div>
  <h1>Computational Geometry</h1>
<svg 
  width="500" 
  height="500"
  style={{ border: '1px solid #ccc' }}
  onClick={(e) => {
    const rect = e.currentTarget.getBoundingClientRect()
    const x = e.clientX - rect.left
    const y = e.clientY - rect.top
    if (!pointA) {
      setPointA({ x, y })
    } else if (!pointB) {
      setPointB({ x, y })
    }
  }}
  >
  <line x1={0} y1={250} x2={500} y2={250} stroke="black" />
  <line x1={250} y1={0} x2={250} y2={500} stroke="black" />
  {pointA && (
    <g>
      <circle cx={pointA.x} cy={pointA.y} r={5} fill="blue" />
      <text x={pointA.x + 8} y={pointA.y} fontSize={12}>A</text>
    </g>
  )}
  {pointB && (
    <g>
      <circle cx={pointB.x} cy={pointB.y} r={5} fill="red" />
      <text x={pointB.x + 8} y={pointB.y} fontSize={12}>B</text>
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
