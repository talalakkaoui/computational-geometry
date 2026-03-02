import { useState } from 'react'
import { useOutletContext } from 'react-router-dom'
import Canvas from '../../components/Canvas'
import { fetchDistance } from '../../api/distance'
import type { Point2D, Theme } from '../../types'

type OutletContext = { theme: Theme }

export default function DistancePage() {
  const { theme } = useOutletContext<OutletContext>()
  const [pointA, setPointA] = useState<Point2D | null>(null)
  const [pointB, setPointB] = useState<Point2D | null>(null)
  const [distance, setDistance] = useState<number | null>(null)

  function handlePointClick(p: Point2D) {
    if (!pointA) {
      setPointA(p)
    } else if (!pointB) {
      setPointB(p)
    }
  }

  async function calculateDistance() {
    if (!pointA || !pointB) return
    const d = await fetchDistance(pointA, pointB)
    setDistance(d)
  }

  function reset() {
    setPointA(null)
    setPointB(null)
    setDistance(null)
  }

  const points = [
    ...(pointA ? [{ point: pointA, label: 'A', color: 'royalblue' }] : []),
    ...(pointB ? [{ point: pointB, label: 'B', color: 'tomato' }] : []),
  ]

  return (
    <div>
      <h2 style={{ marginTop: 0 }}>Point Distance</h2>
      <p style={{ color: theme.tickText, marginBottom: 16 }}>
        Click two points on the canvas to calculate the Euclidean distance between them.
      </p>

      <Canvas points={points} onPointClick={handlePointClick} theme={theme} />

      <div style={{ marginTop: 16, display: 'flex', gap: 12, alignItems: 'center' }}>
        {pointA && pointB && (
          <button onClick={calculateDistance}>Calculate Distance</button>
        )}
        {(pointA || pointB) && (
          <button onClick={reset}>Reset</button>
        )}
        {distance !== null && (
          <span style={{ fontSize: 16 }}>Distance: <strong>{distance.toFixed(4)}</strong></span>
        )}
      </div>
    </div>
  )
}
