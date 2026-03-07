import { useState } from 'react'
import { useOutletContext } from 'react-router-dom'
import Canvas from '../../components/Canvas'
import { fetchLineSegmentIntersection } from '../../api/lineSegmentIntersection'
import type { Point2D, Segment2D, Theme } from '../../types'

export default function LineSegmentIntersectionPage() {
    const { theme } = useOutletContext<{ theme: Theme }>()
    const [segments, setSegments] = useState<Segment2D[]>([])
    const [intersectionPoints, setIntersectionPoints] = useState<Point2D[]>([])

    async function calculateLineSegmentIntersection(segs: Segment2D[]) {
        if (segs.length < 2) return
        const result = await fetchLineSegmentIntersection(segs)
        setIntersectionPoints(result.map(r => r.point))
    }

    function handleShapeComplete(pts: Point2D[]) {
        if (pts.length === 2) {
            setSegments(prev => [...prev, [pts[0], pts[1]]])
        } else if (pts.length >= 3) {
            const newSegs: Segment2D[] = pts.map((p, i) => [p, pts[(i + 1) % pts.length]])
            setSegments(prev => [...prev, ...newSegs])
        }
    }

    function reset() {
        setSegments([])
        setIntersectionPoints([])
    }

    return (
        <div>
            <h2>Line Segment Intersection</h2>
            <p style={{ color: theme.tickText, marginBottom: 16 }}>
                Click points then press Enter: 2 points = segment, 3+ points = polygon.
            </p>
            <Canvas
                points={intersectionPoints.map(p => ({ point: p, label: '', color: 'red' }))}
                segments={segments}
                onShapeComplete={handleShapeComplete}
                theme={theme}
            />
            <button onClick={() => calculateLineSegmentIntersection(segments)}>Calculate</button>
            <button onClick={reset}>Reset</button>
        </div>
    )
}