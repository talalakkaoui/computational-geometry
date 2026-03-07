import { useState } from 'react'
import { useOutletContext } from 'react-router-dom'
import Canvas from '../../components/Canvas'
import { fetchDistance } from '../../api/distance'
import type { Point2D, Theme } from '../../types'

type OutletContext = { theme: Theme }

export default function DistancePage() {
  const { theme } = useOutletContext<OutletContext>()
  const [selectedPoints, setSelectedPoints] = useState<Point2D[]>([])
  const [distance, setDistance] = useState<number | null>(null)
  const [error, setError] = useState<string | null>(null)

  function handleShapeComplete(pts: Point2D[]) {
    if (pts.length !== 1) {
      setError('Please click a single point and press Enter.')
      return
    }
    setError(null)
    setSelectedPoints(prev => [...prev, pts[0]])
  }

  async function calculateDistance() {
    if (selectedPoints.length > 2) {
      setError('Distance requires exactly 2 points.')
      return
    }
    if (selectedPoints.length < 2) return
    const d = await fetchDistance(selectedPoints[0], selectedPoints[1])
    setDistance(d)
  }

  function reset() {
    setSelectedPoints([])
    setDistance(null)
    setError(null)
  }

  const colors = ['royalblue', 'tomato']
  const labels = ['A', 'B']
  const points = selectedPoints.map((p, i) => ({ point: p, label: labels[i] ?? String(i + 1), color: colors[i] ?? 'gray' }))

  return (
    <div>
      <h2 style={{ marginTop: 0 }}>Point Distance</h2>
      <p style={{ color: theme.tickText, marginBottom: 16 }}>
        Click a point then press Enter or Space. Do this twice to set points A and B.
      </p>

      <Canvas points={points} onShapeComplete={handleShapeComplete} theme={theme} />

      {error && <p style={{ color: 'tomato', marginTop: 8 }}>{error}</p>}
      <div style={{ marginTop: 16, display: 'flex', gap: 12, alignItems: 'center' }}>
        {selectedPoints.length === 2 && (
          <button onClick={calculateDistance}>Calculate Distance</button>
        )}
        {selectedPoints.length > 0 && (
          <button onClick={reset}>Reset</button>
        )}
        {distance !== null && (
          <span style={{ fontSize: 16 }}>Distance: <strong>{distance.toFixed(4)}</strong></span>
        )}
      </div>
    </div>
  )
}
